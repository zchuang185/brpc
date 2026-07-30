---
type: "query"
date: "2026-07-30T03:38:33.172347+00:00"
question: "重新编译了，strings ./build/urma_performance_client | grep -F URMA JFCE event queue drained 输出是空的"
contributor: "graphify"
outcome: "useful"
source_nodes: ["UrmaEndpoint", "urma_endpoint.cpp"]
---

# Q: 重新编译了，strings ./build/urma_performance_client | grep -F URMA JFCE event queue drained 输出是空的

## Answer

Expanded from original query via vocab: [client, link, urma]. 当前源码包含日志标记；可执行文件中没有标记说明必须核对 CMakeCache.txt 和 link.txt 中实际 BRPC_LIB。若动态链接，标记应在 libbrpc.so 而非 client；若静态链接且选中库也无标记，则是旧库或未以 BRPC_WITH_URMA 重编译。Make 构建应先生成 libbrpc.a、output/include 和 output/lib，再清理示例 CMake 缓存并显式指定 BRPC_INCLUDE_PATH 与 BRPC_LIB。

## Outcome

- Signal: useful

## Source Nodes

- UrmaEndpoint
- urma_endpoint.cpp