# nanoprintf

本目录集成 nanoprintf v0.8.0，用于提供轻量级的 printf 风格字符串格式化。

## 接入构建

将 `npf_config.c` 加入目标的源文件，并将本目录加入头文件搜索路径：

```cmake
set(NANOPRINTF_DIR ${CMAKE_CURRENT_SOURCE_DIR}/middleware/nanoprintf)

target_sources(${FIRMWARE_TARGET} PRIVATE
    ${NANOPRINTF_DIR}/npf_config.c
)

target_include_directories(${FIRMWARE_TARGET} PRIVATE
    ${NANOPRINTF_DIR}
)
```

## 使用

业务代码必须包含配置包装头，不要直接包含 `nanoprintf.h`：

```c
#include "npf_config.h"

char buffer[64];
int length = npf_snprintf(buffer, sizeof(buffer),
                          "value=%d, voltage=%.2f", 42, 3.3f);
```

当前配置启用了单精度浮点模式。所有调用点统一包含 `npf_config.h`，以保证配置宏、参数包装和实现之间的 ABI 一致。

`npf_config.c` 是唯一允许定义 `NANOPRINTF_IMPLEMENTATION` 的编译单元，不要在其他源文件中重复定义。
