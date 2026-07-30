---
type: "query"
date: "2026-07-30T02:59:25.159516+00:00"
question: "event模式没有收到 URMA completion: ... direction=recv ... length=37"
contributor: "graphify"
outcome: "useful"
source_nodes: ["UrmaEndpoint::PollCq()", "UrmaEndpoint::WaitCqEvent()", "UrmaEndpoint::ReqNotifyCq()", "UrmaEndpoint::HandleCompletion()", "urma_wait_jfc()"]
---

# Q: event模式没有收到 URMA completion: ... direction=recv ... length=37

## Answer

Expanded from original query via vocab: [event, wait, poll, completion, recv, jfc, rearm, notify, handle, endpoint]. 客户端第一条JFC事件和SEND completion证明事件通道、CQ和回调均可工作。根因是bonding JFCE fd本身为聚合epoll fd，brpc又以EPOLLET监听；WaitCqEvent调用urma_wait_jfc(..., jfc_cnt=1)一次只消费一个物理JFC事件。PollCq原先在处理一个事件后立即依赖MoreReadEvents，内层JFCE若仍可读不会产生新的外层边沿，后续37字节RECV completion被留在队列。修复为处理完事件后继续非阻塞WaitCqEvent，直到返回0才调用MoreReadEvents重置外层事件计数；同时增加JFCE queue drained日志。Yalanting使用level/one-shot async_wait，每轮重新等待，因此不会依赖同样的外层ET计数。

## Outcome

- Signal: useful

## Source Nodes

- UrmaEndpoint::PollCq()
- UrmaEndpoint::WaitCqEvent()
- UrmaEndpoint::ReqNotifyCq()
- UrmaEndpoint::HandleCompletion()
- urma_wait_jfc()