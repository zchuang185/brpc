# Graph Report - C:\workspace\code\opensource\brpc\src\brpc\urma  (2026-07-29)

## Corpus Check
- Corpus is ~27,958 words - fits in a single context window. You may not need a graph.

## Summary
- 823 nodes · 1111 edges · 59 communities
- Extraction: 95% EXTRACTED · 5% INFERRED · 0% AMBIGUOUS · INFERRED: 61 edges (avg confidence: 0.8)
- Token cost: 0 input · 0 output

## Community Hubs (Navigation)
- Endpoint Data Path
- Handshake State Machine
- Device Capability Model
- Transport Port Attributes
- Global Runtime Buffer Pool
- Memory Segment Registration
- Work Request Payloads
- Context Address Identity
- Queue Pair Configuration
- Transport Attribute Values
- Core SDK Types
- Endpoint Resource Allocation
- URMA API Lifecycle
- Endpoint Resource Bundle
- Completion Queue Processing
- Mock URMA Backend
- Unreliable Transport Resources
- Completion Queue Internals
- Completion Record Model
- Receive Queue Internals
- Jetty Runtime State
- Jetty Group Runtime
- Parsed Handshake Payload
- Send Queue Internals
- Completion Queue Options
- Receive Queue Options
- Send Queue Options
- Imported Target Jetty
- Atomic Scatter Gather
- Context Event Resources
- Send Work Request
- Device Attribute Record
- Jetty Configuration
- Jetty Group Configuration
- Remote Jetty Identity
- Transport Path Configuration
- Resource Import APIs
- Completion Queue Configuration
- Remote Receive Queue
- Token Identifier Lifecycle
- Transport Configuration Query
- Network Address Model
- Notification Record
- Active Transport Config
- Async Event Model
- Receive Posting Lifecycle
- Congestion Control Entry
- Jetty Runtime Attributes
- Jetty Option State
- Receive Queue Attributes
- Pending Receive Buffer
- Completion Event Wait
- Active Transport Attributes
- Completion Queue Attributes
- Send Queue Attributes
- User Control Input
- User Control Output
- URMA Initialization Attributes
- Service Level Mapping

## God Nodes (most connected - your core abstractions)
1. `urma_device_cap` - 47 edges
2. `urma_tp_attr` - 24 edges
3. `urma_tp_attr_value` - 23 edges
4. `UrmaEndpoint` - 20 edges
5. `HelloMessage` - 19 edges
6. `urma_target_jetty` - 18 edges
7. `urma_jetty_grp` - 17 edges
8. `urma_jetty` - 17 edges
9. `urma_jfc` - 16 edges
10. `UrmaResource` - 16 edges

## Surprising Connections (you probably didn't know these)
- `GlobalUrmaInitializeImpl()` --calls--> `urma_init()`  [INFERRED]
  urma_helper.cpp → mock_urma.cpp
- `GlobalUrmaInitializeImpl()` --calls--> `urma_get_device_list()`  [INFERRED]
  urma_helper.cpp → mock_urma.cpp
- `GlobalUrmaInitializeImpl()` --calls--> `urma_free_device_list()`  [INFERRED]
  urma_helper.cpp → mock_urma.cpp
- `GlobalUrmaInitializeImpl()` --calls--> `urma_query_device()`  [INFERRED]
  urma_helper.cpp → mock_urma.cpp
- `GlobalUrmaInitializeImpl()` --calls--> `urma_get_eid_list()`  [INFERRED]
  urma_helper.cpp → mock_urma.cpp

## Import Cycles
- None detected.

## Communities (59 total, 0 thin omitted)

### Community 0 - "Endpoint Data Path"
Cohesion: 0.05
Nodes (44): AppConnect, IOBuf, ostream, Socket, StringPiece, bthread_tag_t, function, ParsedHello (+36 more)

### Community 1 - "Handshake State Machine"
Cohesion: 0.06
Nodes (49): UrmaEndpoint::FillLocalHelloV2(), UrmaEndpoint::ProcessHandshakeAtServer(), UrmaEndpoint::ReadAndParseHelloV3(), ParsedHello, CreateClientHandshake(), CreateServerHandshakeByMagic(), DrainBytes(), HelloMessage (+41 more)

### Community 2 - "Device Capability Model"
Cohesion: 0.04
Nodes (47): urma_device_cap, atomic_feat, ceq_cnt, congestion_ctrl_alg, feature, max_cas_size, max_eid_cnt, max_fetch_and_add_size (+39 more)

### Community 3 - "Transport Port Attributes"
Cohesion: 0.05
Nodes (42): urma_device, name, ops, path, sysfs_dev, type, urma_net_addr_info, index (+34 more)

### Community 4 - "Global Runtime Buffer Pool"
Cohesion: 0.07
Nodes (36): atomic, urma_delete_context(), urma_register_seg(), urma_uninit(), urma_unregister_seg(), AlignUp(), BufferPool, free_lists (+28 more)

### Community 5 - "Memory Segment Registration"
Cohesion: 0.06
Nodes (36): urma_seg_t, urma_token_t, urma_cr_token, token_id, token_value, urma_seg, attr, urma_seg_cfg (+28 more)

### Community 6 - "Work Request Payloads"
Cohesion: 0.07
Nodes (29): urma_target_seg_t, urma_jfr_wr, next, src, user_ctx, urma_rw_wr, dst, notify_data (+21 more)

### Community 7 - "Context Address Identity"
Cohesion: 0.07
Nodes (29): urma_context, aggr_mode, async_fd, dev, dev_fd, eid, eid_index, mutex (+21 more)

### Community 8 - "Queue Pair Configuration"
Cohesion: 0.08
Nodes (25): urma_jfc_t, urma_jfr_cfg, depth, flag, id, jfc, max_sge, min_rnr_timer (+17 more)

### Community 9 - "Transport Attribute Values"
Cohesion: 0.09
Nodes (23): urma_tp_attr_value, ack_udp_srcport, at, at_times, data_udp_srcport, dip, dma, dscp (+15 more)

### Community 10 - "Core SDK Types"
Cohesion: 0.12
Nodes (15): urma_guid, raw, urma_jfce_cfg, depth, user_ctx, urma_ops, urma_provider_ops, urma_ref (+7 more)

### Community 11 - "Endpoint Resource Allocation"
Cohesion: 0.19
Nodes (16): urma_context_t, urma_jetty_cfg_t, urma_jfc_cfg_t, urma_jfce_t, urma_jfr_cfg_t, urma_create_jetty(), urma_create_jfc(), urma_create_jfce() (+8 more)

### Community 12 - "URMA API Lifecycle"
Cohesion: 0.18
Nodes (15): urma_jetty_t, urma_status_t, urma_target_jetty_t, urma_bind_jetty(), urma_delete_jetty(), urma_delete_jfc(), urma_init(), urma_modify_jetty() (+7 more)

### Community 13 - "Endpoint Resource Bundle"
Cohesion: 0.12
Nodes (16): urma_jetty_t, urma_jfc_t, urma_jfce_t, urma_jfr_t, urma_target_jetty_t, urma_target_seg_t, PreparedJetty, res (+8 more)

### Community 14 - "Completion Queue Processing"
Cohesion: 0.18
Nodes (14): deque, mutex, urma_cr_t, urma_jfc_t, JfcState, completions, event_pending, mutex (+6 more)

### Community 15 - "Mock URMA Backend"
Cohesion: 0.22
Nodes (13): urma_ack_async_event(), urma_create_context(), urma_free_device_list(), urma_free_eid_list(), urma_get_async_event(), urma_get_device_by_name(), urma_get_device_list(), urma_get_eid_list() (+5 more)

### Community 16 - "Unreliable Transport Resources"
Cohesion: 0.14
Nodes (14): urma_ur, attr, urma_ur_info, attr, cnt, name, seg_list, size (+6 more)

### Community 17 - "Completion Queue Internals"
Cohesion: 0.15
Nodes (13): urma_jfc_cfg_t, urma_jfc, async_events_acked, comp_events_acked, event_cond, event_mutex, handle, jfc_cfg (+5 more)

### Community 18 - "Completion Record Model"
Cohesion: 0.15
Nodes (13): urma_cr, completion_len, flag, local_id, opcode, remote_id, status, tpn (+5 more)

### Community 19 - "Receive Queue Internals"
Cohesion: 0.17
Nodes (12): pthread_mutex_t, urma_jfr_cfg_t, urma_jfr, async_events_acked, event_cond, event_mutex, handle, jfr_cfg (+4 more)

### Community 20 - "Jetty Runtime State"
Cohesion: 0.17
Nodes (12): urma_jetty_cfg_t, urma_jetty, async_events_acked, event_cond, event_mutex, handle, jetty_cfg, jetty_id (+4 more)

### Community 21 - "Jetty Group Runtime"
Cohesion: 0.17
Nodes (12): urma_jetty_t, urma_jetty_grp, async_events_acked, event_cond, event_mutex, handle, jetty_cnt, jetty_grp_id (+4 more)

### Community 22 - "Parsed Handshake Payload"
Cohesion: 0.17
Nodes (12): ParsedHello, buffer_size, eid, jetty_id, recv_buffer_cnt, seg_eid, seg_len, seg_token_id (+4 more)

### Community 23 - "Send Queue Internals"
Cohesion: 0.18
Nodes (11): pthread_cond_t, urma_jfs, async_events_acked, event_cond, event_mutex, handle, jfs_cfg, jfs_id (+3 more)

### Community 24 - "Completion Queue Options"
Cohesion: 0.18
Nodes (11): urma_jfc_opt, is_actived, jfc_opt_mask, reserved, urma_jfc_ci, urma_jfc_cqe_base_addr, urma_jfc_db_addr, urma_jfc_db_status (+3 more)

### Community 25 - "Receive Queue Options"
Cohesion: 0.18
Nodes (11): urma_jfr_opt, is_actived, jfr_opt_mask, reserved, urma_jfr_ci, urma_jfr_db_addr, urma_jfr_db_status, urma_jfr_id (+3 more)

### Community 26 - "Send Queue Options"
Cohesion: 0.18
Nodes (11): urma_jfs_opt, is_actived, jfs_opt_mask, reserved, urma_jfs_ci, urma_jfs_db_addr, urma_jfs_db_status, urma_jfs_id (+3 more)

### Community 27 - "Imported Target Jetty"
Cohesion: 0.18
Nodes (11): urma_target_jetty, flag, handle, id, policy, tp, tp_type, trans_mode (+3 more)

### Community 28 - "Atomic Scatter Gather"
Cohesion: 0.20
Nodes (10): urma_sge_t, urma_cas_wr, dst, src, urma_faa_wr, dst, src, urma_sg (+2 more)

### Community 29 - "Context Event Resources"
Cohesion: 0.22
Nodes (9): urma_context_t, urma_jfce, fd, ref, urma_ctx, urma_notifier, fd, incomplete_tjetty_list (+1 more)

### Community 30 - "Send Work Request"
Cohesion: 0.22
Nodes (9): urma_target_jetty_t, urma_jfs_wr, flag, next, opcode, tjetty, user_ctx, urma_jfs_wr_flag_t (+1 more)

### Community 31 - "Device Attribute Record"
Cohesion: 0.22
Nodes (9): urma_device_attr, dev_cap, guid, port_attr, port_cnt, reserved_jetty_id_max, reserved_jetty_id_min, urma_device_cap_t (+1 more)

### Community 32 - "Jetty Configuration"
Cohesion: 0.22
Nodes (9): urma_jetty_cfg, flag, id, jetty_grp, jfs_cfg, user_ctx, urma_jetty_flag_t, urma_jetty_grp_t (+1 more)

### Community 33 - "Jetty Group Configuration"
Cohesion: 0.22
Nodes (9): urma_jetty_grp_cfg, flag, id, name, policy, token_value, user_ctx, urma_jetty_grp_flag_t (+1 more)

### Community 34 - "Remote Jetty Identity"
Cohesion: 0.22
Nodes (9): urma_rjetty, flag, jetty_id, policy, tp_type, trans_mode, type, urma_jetty_id_t (+1 more)

### Community 35 - "Transport Path Configuration"
Cohesion: 0.22
Nodes (9): urma_tp_cfg, ack_timeout, dscp, flag, oor_cnt, retry_factor, retry_num, trans_mode (+1 more)

### Community 36 - "Resource Import APIs"
Cohesion: 0.25
Nodes (8): urma_seg_t, urma_target_seg_t, urma_token_t, urma_import_jetty(), urma_import_seg(), urma_unimport_seg(), urma_import_seg_flag_t, urma_rjetty_t

### Community 37 - "Completion Queue Configuration"
Cohesion: 0.25
Nodes (8): urma_jfce_t, urma_jfc_cfg, ceqn, depth, flag, jfce, user_ctx, urma_jfc_flag_t

### Community 38 - "Remote Receive Queue"
Cohesion: 0.25
Nodes (8): urma_rjfr, flag, jfr_id, tp_type, trans_mode, urma_import_jetty_flag_t, urma_jfr_id_t, urma_tp_type_t

### Community 39 - "Token Identifier Lifecycle"
Cohesion: 0.25
Nodes (8): urma_token_id, flag, handle, ref, token_id, urma_ctx, urma_ref_t, urma_token_id_flag_t

### Community 40 - "Transport Configuration Query"
Cohesion: 0.29
Nodes (7): urma_get_tp_cfg, flag, local_eid, peer_eid, trans_mode, urma_get_tp_cfg_flag_t, urma_transport_mode_t

### Community 41 - "Network Address Model"
Cohesion: 0.33
Nodes (6): sa_family_t, urma_net_addr, mac, prefix_len, sin_family, vlan

### Community 42 - "Notification Record"
Cohesion: 0.33
Nodes (6): urma_status_t, urma_notify, status, type, user_ctx, urma_notify_type_t

### Community 43 - "Active Transport Config"
Cohesion: 0.33
Nodes (6): urma_active_tp_cfg, peer_tp_handle, tag, tp_attr, tp_handle, urma_active_tp_attr_t

### Community 44 - "Async Event Model"
Cohesion: 0.33
Nodes (6): urma_async_event, element, event_type, priv, urma_ctx, urma_async_event_type_t

### Community 45 - "Receive Posting Lifecycle"
Cohesion: 0.40
Nodes (5): urma_jfr_t, urma_delete_jfr(), urma_post_jfr_wr(), UrmaEndpoint::DoPostRecv(), urma_jfr_wr_t

### Community 46 - "Congestion Control Entry"
Cohesion: 0.40
Nodes (5): urma_cc_entry, alg, cc_pattern_idx, cc_priority, urma_tp_cc_alg_t

### Community 47 - "Jetty Runtime Attributes"
Cohesion: 0.40
Nodes (5): urma_jetty_attr, mask, rx_threshold, state, urma_jetty_state_t

### Community 48 - "Jetty Option State"
Cohesion: 0.40
Nodes (5): urma_jetty_opt, is_actived, jfs_opt, reserved, urma_jfs_opt_t

### Community 49 - "Receive Queue Attributes"
Cohesion: 0.40
Nodes (5): urma_jfr_attr, mask, rx_threshold, state, urma_jfr_state_t

### Community 50 - "Pending Receive Buffer"
Cohesion: 0.50
Nodes (4): PendingRecv, addr, len, user_ctx

### Community 51 - "Completion Event Wait"
Cohesion: 0.50
Nodes (4): urma_wait_jfc(), SocketUniquePtr, urma_jfc_t, UrmaEndpoint::WaitCqEvent()

### Community 52 - "Active Transport Attributes"
Cohesion: 0.50
Nodes (4): urma_active_tp_attr, reserved, rx_psn, tx_psn

### Community 53 - "Completion Queue Attributes"
Cohesion: 0.50
Nodes (4): urma_jfc_attr, mask, moderate_count, moderate_period

### Community 54 - "Send Queue Attributes"
Cohesion: 0.50
Nodes (4): urma_jfs_attr, mask, state, urma_jfs_state_t

### Community 55 - "User Control Input"
Cohesion: 0.50
Nodes (4): urma_user_ctl_in, addr, len, opcode

### Community 56 - "User Control Output"
Cohesion: 0.50
Nodes (4): urma_user_ctl_out, addr, len, reserved

### Community 57 - "URMA Initialization Attributes"
Cohesion: 0.67
Nodes (3): urma_init_attr, token, uasid

### Community 58 - "Service Level Mapping"
Cohesion: 0.67
Nodes (3): urma_sl_info, SL, tp_type

## Knowledge Gaps
- **458 isolated node(s):** `mutex`, `completions`, `event_pending`, `addr`, `len` (+453 more)
  These have ≤1 connection - possible missing edges or undocumented components.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `urma_device_cap` connect `Device Capability Model` to `Core SDK Types`?**
  _High betweenness centrality (0.109) - this node is a cross-community bridge._
- **Why does `urma_tp_attr_value` connect `Transport Attribute Values` to `Core SDK Types`?**
  _High betweenness centrality (0.053) - this node is a cross-community bridge._
- **Why does `urma_tp_attr` connect `Transport Port Attributes` to `Core SDK Types`?**
  _High betweenness centrality (0.052) - this node is a cross-community bridge._
- **Are the 3 inferred relationships involving `UrmaEndpoint` (e.g. with `UrmaEndpoint::PollCq()` and `UrmaEndpoint::ProcessHandshakeAtClient()`) actually correct?**
  _`UrmaEndpoint` has 3 INFERRED edges - model-reasoned connections that need verification._
- **What connects `mutex`, `completions`, `event_pending` to the rest of the system?**
  _458 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Endpoint Data Path` be split into smaller, more focused modules?**
  _Cohesion score 0.05027322404371585 - nodes in this community are weakly interconnected._
- **Should `Handshake State Machine` be split into smaller, more focused modules?**
  _Cohesion score 0.05536723163841808 - nodes in this community are weakly interconnected._