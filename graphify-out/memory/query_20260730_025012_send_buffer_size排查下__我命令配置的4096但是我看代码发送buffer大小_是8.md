---
type: "query"
date: "2026-07-30T02:50:12.073028+00:00"
question: "send buffer_size排查下， 我命令配置的4096但是我看代码发送buffer大小 是8*1024"
contributor: "graphify"
outcome: "useful"
source_nodes: ["GlobalUrmaInitializeImpl()", "GetUrmaRecvBlockSize()", "UrmaEndpoint::MakeLocalParsedHello()", "UrmaEndpoint::ApplyRemoteHello()", "UrmaEndpoint::CutFromIOBufList()", "UrmaEndpoint::PostRecv()"]
---

# Q: send buffer_size排查下， 我命令配置的4096但是我看代码发送buffer大小 是8*1024

## Answer

Expanded from original query via vocab: [urma, buffer, size, send, block, pool, recv, cut, sge, initialize]. 结论：8*1024只出现在urma_buffer_size默认值和g_recv_block_size初始化前默认值。命令行4096在GlobalUrmaInitializeImpl中生效：pool raw block为4096，IOBuf默认块改为4096，扣除32字节IOBuf::Block头后GetUrmaRecvBlockSize为4064。握手广告4064，ApplyRemoteHello保存对端值，CutFromIOBufList以_remote_recv_block_size为单个SEND WR总payload上限，所以双方都配置4096时SEND不会超过4064；一端仍为默认8192时，向该端发送的上限会是8160。示例在创建Channel/Server前解析gflags，初始化时序正确。

## Outcome

- Signal: useful

## Source Nodes

- GlobalUrmaInitializeImpl()
- GetUrmaRecvBlockSize()
- UrmaEndpoint::MakeLocalParsedHello()
- UrmaEndpoint::ApplyRemoteHello()
- UrmaEndpoint::CutFromIOBufList()
- UrmaEndpoint::PostRecv()