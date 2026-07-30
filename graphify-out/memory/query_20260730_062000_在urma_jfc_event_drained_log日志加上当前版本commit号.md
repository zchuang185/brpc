---
type: "query"
date: "2026-07-30T06:20:00.366442+00:00"
question: "在URMA JFC event drained log日志加上当前版本commit号"
contributor: "graphify"
outcome: "useful"
source_nodes: ["UrmaEndpoint", "urma_endpoint.cpp"]
---

# Q: 在URMA JFC event drained log日志加上当前版本commit号

## Answer

Expanded from original query via vocab: [version, urma, jfce, event, drain]. 复用仓库已有 BRPC_REVISION 编译宏，在 URMA JFCE event queue drained 日志中追加 build_revision；其格式包含 release、branch、短 commit 和提交时间，未定义时输出 undefined。

## Outcome

- Signal: useful

## Source Nodes

- UrmaEndpoint
- urma_endpoint.cpp