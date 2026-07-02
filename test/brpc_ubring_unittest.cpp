// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to You under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <gtest/gtest.h>
#include "butil/macros.h"
#include "brpc/socket.h"

#if BRPC_WITH_UBRING
#include "brpc/ubshm/ub_endpoint.h"

namespace brpc {
namespace ubring {
extern bool g_skip_ub_init;
}  // namespace ubring
}  // namespace brpc

class UBShmEndpointTest : public ::testing::Test {
protected:
    void SetUp() override {
        _saved_skip = brpc::ubring::g_skip_ub_init;
        brpc::ubring::g_skip_ub_init = true;

        brpc::SocketOptions options;
        ASSERT_EQ(0, brpc::Socket::Create(options, &_socket_id));
        brpc::SocketUniquePtr s;
        ASSERT_EQ(0, brpc::Socket::Address(_socket_id, &s));
        _socket = s.get();
        _ep = new brpc::ubring::UBShmEndpoint(_socket);
    }

    void TearDown() override {
        delete _ep;
        brpc::SocketUniquePtr s;
        if (brpc::Socket::Address(_socket_id, &s) == 0) {
            s->SetFailed();
        }
        brpc::ubring::g_skip_ub_init = _saved_skip;
    }

    brpc::SocketId _socket_id = brpc::INVALID_SOCKET_ID;
    brpc::Socket* _socket = nullptr;
    brpc::ubring::UBShmEndpoint* _ep = nullptr;
    bool _saved_skip = false;
};

TEST_F(UBShmEndpointTest, construct_and_destruct) {
    ASSERT_NE(nullptr, _ep);
}

TEST_F(UBShmEndpointTest, is_writable_false_when_skip_init) {
    ASSERT_FALSE(_ep->IsWritable());
}

TEST_F(UBShmEndpointTest, reset_is_idempotent) {
    _ep->Reset();
    _ep->Reset();
}

#else

TEST(UBShmEndpointTest, ubring_disabled) {
    SUCCEED() << "BRPC_WITH_UBRING is not enabled, skip.";
}

#endif  // BRPC_WITH_UBRING
