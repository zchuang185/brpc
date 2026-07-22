// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "brpc/urma/urma_handshake.h"

#if BRPC_WITH_URMA

#include <algorithm>
#include <cstring>

#include "butil/logging.h"
#include "butil/sys_byteorder.h"

#include "brpc/urma/urma_endpoint.h"
#include "brpc/urma_transport.h"

namespace brpc {
namespace urma {

// ============================================================================
// v2 binary HelloMessage Serialize / Deserialize.
// On-wire layout (network byte order, tightly packed body of 82 bytes):
//
//   offset  field            size
//      0    msg_len          2B    (full packet length incl. magic)
//      2    hello_ver        2B
//      4    impl_ver         2B
//      6    buffer_size      4B
//     10    recv_buffer_cnt  4B
//     14    jetty_id         4B
//     18    eid             16B    (raw, no swap)
//     34    uasid            4B
//     38    tp_type          1B
//     39    pad              3B
//     42    seg_eid         16B    (raw)
//     58    seg_uasid        4B
//     62    seg_va           8B
//     70    seg_len          8B
//     78    seg_token_id     4B
//   total = 82 bytes body.
//
// Full packet = magic "URMA" (4B) + body (82B) = 86 bytes.
// ============================================================================

namespace v2_wire {

void HelloMessage::Serialize(void* buf) const {
    uint8_t* p = static_cast<uint8_t*>(buf);
    *(uint16_t*)p = butil::HostToNet16(msg_len);          p += 2;
    *(uint16_t*)p = butil::HostToNet16(hello_ver);        p += 2;
    *(uint16_t*)p = butil::HostToNet16(impl_ver);         p += 2;
    *(uint32_t*)p = butil::HostToNet32(buffer_size);      p += 4;
    *(uint32_t*)p = butil::HostToNet32(recv_buffer_cnt);  p += 4;
    *(uint32_t*)p = butil::HostToNet32(jetty_id);         p += 4;
    memcpy(p, eid, 16);                                   p += 16;
    *(uint32_t*)p = butil::HostToNet32(uasid);            p += 4;
    *p = tp_type;                                         p += 1;
    memset(p, 0, 3);                                     p += 3;  // pad
    memcpy(p, seg_eid, 16);                              p += 16;
    *(uint32_t*)p = butil::HostToNet32(seg_uasid);       p += 4;
    *(uint64_t*)p = butil::HostToNet64(seg_va);           p += 8;
    *(uint64_t*)p = butil::HostToNet64(seg_len);          p += 8;
    *(uint32_t*)p = butil::HostToNet32(seg_token_id);     p += 4;
}

void HelloMessage::Deserialize(const void* buf) {
    const uint8_t* p = static_cast<const uint8_t*>(buf);
    msg_len         = butil::NetToHost16(*(uint16_t*)p);  p += 2;
    hello_ver       = butil::NetToHost16(*(uint16_t*)p);  p += 2;
    impl_ver        = butil::NetToHost16(*(uint16_t*)p);  p += 2;
    buffer_size     = butil::NetToHost32(*(uint32_t*)p);  p += 4;
    recv_buffer_cnt = butil::NetToHost32(*(uint32_t*)p);  p += 4;
    jetty_id        = butil::NetToHost32(*(uint32_t*)p);  p += 4;
    memcpy(eid, p, 16);                                    p += 16;
    uasid           = butil::NetToHost32(*(uint32_t*)p);  p += 4;
    tp_type         = *p;                                 p += 1;
    p += 3;  // pad
    memcpy(seg_eid, p, 16);                                p += 16;
    seg_uasid       = butil::NetToHost32(*(uint32_t*)p);  p += 4;
    seg_va          = butil::NetToHost64(*(uint64_t*)p);  p += 8;
    seg_len         = butil::NetToHost64(*(uint64_t*)p);  p += 8;
    seg_token_id    = butil::NetToHost32(*(uint32_t*)p);  p += 4;
}

}  // namespace v2_wire

// ============================================================================
// Shared helpers.
// ============================================================================

namespace {

constexpr uint32_t MIN_BUFFER_SIZE = 1024;
constexpr uint32_t MIN_BUFFER_CNT = 1;
constexpr uint32_t MAX_BUFFER_CNT = 65535;

bool ValidHello(const ParsedHello& h) {
    if (h.buffer_size < MIN_BUFFER_SIZE) { return false; }
    if (h.recv_buffer_cnt < MIN_BUFFER_CNT || h.recv_buffer_cnt > MAX_BUFFER_CNT) {
        return false;
    }
    if (h.jetty_id == 0) { return false; }
    if (h.tp_type > static_cast<uint8_t>(URMA_UTP)) { return false; }
    if (h.seg_len == 0 || h.seg_va == 0) { return false; }
    return true;
}

}  // namespace

int DrainBytes(UrmaEndpoint* ep, size_t n) {
    char buf[4096];
    while (n > 0) {
        size_t want = std::min(n, sizeof(buf));
        if (ep->ReadFromFd(buf, want) < 0) { return -1; }
        n -= want;
    }
    return 0;
}

int ReadBodyAndNegotiate(UrmaEndpoint* ep, ParsedHello* out, bool* negotiated) {
    *negotiated = false;
    uint8_t body[v2_wire::HELLO_BODY_LEN];
    if (ep->ReadFromFd(body, v2_wire::HELLO_BODY_LEN) < 0) { return -1; }
    v2_wire::HelloMessage m;
    m.Deserialize(body);
    if (m.hello_ver != v2_wire::HELLO_V2_VERSION ||
        m.impl_ver != v2_wire::IMPL_V2_VERSION) { return 0; }
    ParsedHello p;
    p.buffer_size = m.buffer_size;
    p.recv_buffer_cnt = m.recv_buffer_cnt;
    p.jetty_id = m.jetty_id;
    memcpy(p.eid, m.eid, 16);
    p.uasid = m.uasid;
    p.tp_type = m.tp_type;
    memcpy(p.seg_eid, m.seg_eid, 16);
    p.seg_uasid = m.seg_uasid;
    p.seg_va = m.seg_va;
    p.seg_len = m.seg_len;
    p.seg_token_id = m.seg_token_id;
    if (!ValidHello(p)) { return 0; }
    // Drain trailing bytes if msg_len advertises more than the fixed body.
    if (m.msg_len > v2_wire::HELLO_PACKET_LEN) {
        if (DrainBytes(ep, m.msg_len - v2_wire::HELLO_PACKET_LEN) < 0) { return -1; }
    }
    *out = p;
    *negotiated = true;
    return 0;
}

// ============================================================================
// Send / receive.
// ============================================================================

int SendLocalHello(UrmaEndpoint* ep) {
    v2_wire::HelloMessage m;
    ep->FillLocalHelloV2(&m);
    // If we are falling back, zero the version fields so the peer rejects it.
    auto* tp = static_cast<UrmaTransport*>(ep->_socket->_transport.get());
    if (tp->_urma_state == UrmaTransport::URMA_OFF) {
        m.hello_ver = 0;
        m.impl_ver = 0;
        m.jetty_id = 0;
        m.buffer_size = 0;
    }
    uint8_t packet[v2_wire::HELLO_PACKET_LEN];
    memcpy(packet, "URMA", 4);
    m.Serialize(packet + 4);
    return ep->WriteToFd(packet, v2_wire::HELLO_PACKET_LEN);
}

int ReceiveAndParseRemoteHello(UrmaEndpoint* ep, ParsedHello* out,
                                bool* negotiated) {
    // Client side: read the 4B magic first.
    *negotiated = false;
    uint8_t magic[v2_wire::MAGIC_STR_LEN];
    if (ep->ReadFromFd(magic, v2_wire::MAGIC_STR_LEN) < 0) { return -1; }
    if (memcmp(magic, "URMA", 4) != 0) {
        // Peer is not URMA-capable; push the magic back so the TCP input
        // messenger can re-parse it.
        ep->PushBackToReadBuf(magic, v2_wire::MAGIC_STR_LEN);
        return 0;
    }
    return ReadBodyAndNegotiate(ep, out, negotiated);
}

int ReceiveAndParseRemoteHelloServer(UrmaEndpoint* ep, ParsedHello* out,
                                      bool* negotiated) {
    // Server side: the magic was already consumed and verified by the caller.
    return ReadBodyAndNegotiate(ep, out, negotiated);
}

}  // namespace urma
}  // namespace brpc

#endif  // if BRPC_WITH_URMA
