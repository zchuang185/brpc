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

#ifndef BRPC_URMA_HELPER_H
#define BRPC_URMA_HELPER_H

#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>

#include "bthread/types.h"
#include "butil/atomicops.h"

#if BRPC_WITH_URMA

#include "urma/urma_api.h"
#include "urma/urma_types.h"

namespace brpc {
namespace urma {

// Initialize the URMA environment.
// Exit the process if initialization fails.
void GlobalUrmaInitializeOrDie();

// Initialize URMA polling mode for a given bthread tag.
// Returns false on failure.
bool InitPollingModeWithTag(bthread_tag_t tag,
                            std::function<void(void)> callback = nullptr,
                            std::function<void(void)> init_fn = nullptr,
                            std::function<void(void)> release_fn = nullptr);

void ReleasePollingModeWithTag(bthread_tag_t tag);

// Register the given user buffer for URMA access.
// Returns the (opaque, non-zero) target segment handle stored in the user-mr
// table; 0 on failure. To use the memory in an IOBuf, append it via
// append_user_data_with_meta and pass the returned handle as the data meta.
uint32_t RegisterMemoryForUrma(void* buf, size_t len);

// Deregister a previously registered user buffer.
void DeregisterMemoryForUrma(void* buf);

// Return the registered-segment handle for a given address, or 0 if the
// address is not in any region managed by the URMA buffer pool or the user-mr
// table. The handle is carried by urma_sge_t.tseg on the send path.
uint32_t GetSegHandle(void* buf);

// Get the global URMA context (the urma_context_t created on the selected
// device / EID). Returns NULL if URMA is not initialized.
urma_context_t* GetUrmaContext();

// If the URMA environment is available.
bool IsUrmaAvailable();

// Disable URMA for the remaining lifetime of the process.
void GlobalDisableUrma();

// If the given protocol is supported by UrmaTransport.
// Currently only "baidu_std" is supported.
bool SupportedByUrma(std::string protocol);

// Return the configured recv buffer size (one URMA recv WR's payload size).
size_t GetUrmaRecvBlockSize();

// Return max_sge supported by the device.
int GetUrmaMaxSge();

}  // namespace urma
}  // namespace brpc

#else  // if BRPC_WITH_URMA

namespace brpc {
namespace urma {

// Initialize the URMA environment.
// Exit the process if initialization fails.
void GlobalUrmaInitializeOrDie();

}  // namespace urma
}  // namespace brpc

#endif  // if BRPC_WITH_URMA

#endif  // BRPC_URMA_HELPER_H
