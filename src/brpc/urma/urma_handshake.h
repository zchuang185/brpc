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

#ifndef BRPC_URMA_HANDSHAKE_H
#define BRPC_URMA_HANDSHAKE_H

#include <cstdint>
#include <cstring>
#include <string>

#include "urma_types.h"

namespace brpc {
namespace urma {

class UrmaEndpoint;

// Wire-format-agnostic view of a peer's hello message. The endpoint
// uses ApplyRemoteHello to size its send/recv windows and to drive
// urma_import_seg / urma_import_jetty.
struct ParsedHello {
    uint32_t buffer_size = 0;      // peer recv buffer size in bytes (per WR)
    uint32_t recv_buffer_cnt = 0;  // peer recv buffer count (RQ depth - 1)
    uint32_t jetty_id = 0;         // peer jetty id
    uint8_t  eid[16] = {0};         // peer EID (network order)
    uint32_t uasid = 0;             // peer uasid
    uint8_t  tp_type = 0;           // urma_tp_type_t: URMA_RTP / URMA_CTP / URMA_UTP

    // Flattened peer buffer-pool segment.
    uint8_t  seg_eid[16] = {0};     // EID owning the peer segment
    uint32_t seg_uasid = 0;         // uasid owning the peer segment
    uint64_t seg_va = 0;            // segment virtual address
    uint64_t seg_len = 0;           // segment length in bytes
    uint32_t seg_token_id = 0;      // segment token id
};

// Binary wire format. The full on-wire packet is:
//   [ "URMA" 4B ][ HelloMessage body 82B ]   => 86 bytes total.
namespace v2_wire {

constexpr size_t MAGIC_STR_LEN = 4;
constexpr size_t HELLO_BODY_LEN = 82;
constexpr size_t HELLO_PACKET_LEN = MAGIC_STR_LEN + HELLO_BODY_LEN;  // 86
constexpr size_t HELLO_MSG_LEN_MAX = 4096;
constexpr uint16_t HELLO_V2_VERSION = 2;
constexpr uint16_t IMPL_V2_VERSION = 1;

// The serializable struct. Serialized to network byte order.
struct HelloMessage {
    uint16_t msg_len;       // total packet length (incl. magic)
    uint16_t hello_ver;
    uint16_t impl_ver;
    uint32_t buffer_size;
    uint32_t recv_buffer_cnt;
    uint32_t jetty_id;
    uint8_t  eid[16];
    uint32_t uasid;
    uint8_t  tp_type;
    uint8_t  pad[3];        // keep the struct 4-byte aligned
    uint8_t  seg_eid[16];
    uint32_t seg_uasid;
    uint64_t seg_va;
    uint64_t seg_len;
    uint32_t seg_token_id;

    void Serialize(void* buf) const;   // host -> network order, write to buf
    void Deserialize(const void* buf); // network -> host order, read from buf
};

}  // namespace v2_wire

// Send the local hello over the TCP fd held by the endpoint.
// Returns 0 on success, -1 on failure (errno set).
int SendLocalHello(UrmaEndpoint* ep);

// Client-side: read the 4B magic first, verify it's "URMA", then read the
// body. If the magic is not "URMA", push the bytes back and set
// *negotiated=false (fall back to TCP).
// Returns -1 on IO error (errno set).
int ReceiveAndParseRemoteHello(UrmaEndpoint* ep, ParsedHello* out,
                                bool* negotiated);

// Server-side: the magic was already consumed by the caller. Read the body
// and parse. Sets *negotiated=false (return 0) if the message is invalid.
// Returns -1 on IO error.
int ReceiveAndParseRemoteHelloServer(UrmaEndpoint* ep, ParsedHello* out,
                                      bool* negotiated);

// Drain @n bytes from the TCP fd.
int DrainBytes(UrmaEndpoint* ep, size_t n);

// Read the body following the magic and translate to ParsedHello.
// Friend of UrmaEndpoint. Returns -1 on IO error; 0 with *negotiated=false
// on invalid (peer not URMA-capable); 0 with *negotiated=true on success.
int ReadBodyAndNegotiate(UrmaEndpoint* ep, ParsedHello* out, bool* negotiated);

}  // namespace urma
}  // namespace brpc

#endif  // BRPC_URMA_HANDSHAKE_H
