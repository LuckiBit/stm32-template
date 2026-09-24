# STM32F103ZE 固件工程

仓库根目录包含两个相互独立的固件工程：

- `bootloader`：裸机启动、Application 向量检查与跳转；固件升级与回滚为预留功能。
- `application`：FreeRTOS 分阶段启动、常驻系统管理、编号任务与资源、LED 示例。

两个工程都使用 CMake、Ninja 和 `arm-none-eabi-gcc` 构建，并分别提供自己的 `CMakePresets.json`。

## 当前架构

两个工程均沿用 `app`、`core`、`hardware`、`service`、`middleware` 五层源码结构。
`cmake`、`build` 和根目录的 `docs` 分别用于构建工具、生成产物和文档。

Application 的 `app/tasks/tasks.h` 集中控制 16 个编号任务槽位和配套资源的编译期开关。
`core/rtos_start.c` 创建启用项并启动调度器；`app/system_manager` 只等待已启用任务就绪，
放行后常驻接收故障。任务入口位于 `app/tasks`，LED 流程、服务与硬件操作分别位于
`app/led`、`service/led`、`hardware/bsp/gpio`。

默认只启用 LED 的 `task_4`，实际共 **3 个任务**：LED、系统管理和 FreeRTOS 空闲任务。
8 个队列、8 个二值信号量、8 个互斥量、4 个业务事件组、4 个软件定时器均为可选槽位，
默认不创建；禁用任务和资源不占静态 RTOS 存储。启用事件任务 0、1 时默认自动启用其
定时器和事件组。软件定时器服务只在需要时创建；全部 16 个业务任务开启时总计 19 个任务。

- [整个工程的结构、职责、Bootloader 流程和 Flash 布局](docs/firmware_arch.md)。
- [Application 的任务清单、启动协议、静态资源与故障处理](docs/rtos_startup.md)。
- [C 编码规范与项目约定](docs/c_coding_standard.md)。
- [GPIO 引脚分配、功能与用途](docs/pin_assignment.md)。

## 调试串口

Bootloader 和 Application 均在 `system_init()` 中按开关初始化 F1 的 5 路串口，默认参数为 **115200、8 数据位、无校验、1 停止位**，
无硬件流控。当前仅启用串口 1：PA9 为 TX、PA10 为 RX。
连接 3.3 V USB 转串口模块时，PA9 接模块 RX、PA10 接模块 TX，并共地。

`hardware/bsp/uart/bsp_uart.h` 中的 `BSP_UART_1_ENABLE` 至 `BSP_UART_5_ENABLE` 控制每路串口是否初始化，
默认值可通过 CMake 编译定义覆盖；
原始发送统一使用 `bsp_uart_transmit()`。格式化发送使用 `service/my_printf` 提供的 `my_printf()`，
默认仅向串口 1 输出，可在 `my_printf_config.h` 中分别启用 1～5 路输出并修改缓冲区容量和超时；
这些默认值也可通过 CMake 编译定义覆盖。Application 服务通过静态互斥量串行化多任务发送，
Bootloader 服务使用单线程裸机实现；两者均未重定向 libc `printf`。

每路配置独立成组：`BSP_UART_BAUD_RATE_n`、`BSP_UART_WORD_LENGTH_n`、
`BSP_UART_STOP_BITS_n`、`BSP_UART_PARITY_n`、`BSP_UART_MODE_n`、
`BSP_UART_HW_FLOW_CONTROL_n` 和 `BSP_UART_OVERSAMPLING_n`（n 为 1～5）。
例如修改 `BSP_UART_BAUD_RATE_2` 只影响串口 2；各路初始化分别读取自己的配置。
参数须符合芯片能力；启用硬件流控还需配置对应引脚。

TX/RX 端口、引脚、GPIO 时钟和 USART 重映射也按路集中在 `bsp_uart.h`，
由 `bsp_uart.c` 中的 `HAL_UART_MspInit()` 应用。修改引脚时需同步对应 GPIO 时钟和
芯片支持的重映射配置。状态 LED 使用 PA5；使用 PA5 的复用功能（如 SPI1_SCK）前需解决引脚占用。

| 串口编号 | HAL 外设 | TX | RX | 默认开关 |
| --- | --- | --- | --- | --- |
| 1 | USART1 | PA9 | PA10 | 开启 |
| 2 | USART2 | PA2 | PA3 | 关闭 |
| 3 | USART3 | PB10 | PB11 | 关闭 |
| 4 | UART4 | PC10 | PC11 | 关闭 |
| 5 | UART5 | PC12 | PD2 | 关闭 |

## 环境要求

确认以下工具可用：

```bash
cmake --version
ninja --version
arm-none-eabi-gcc --version
```

## 构建 Bootloader

进入工程目录：

```bash
cd bootloader
```

Debug 配置和构建：

```bash
cmake --preset debug
cmake --build --preset debug
```

Release 配置和构建：

```bash
cmake --preset release
cmake --build --preset release
```

完成首次配置后，日常增量构建只需执行：

```bash
cmake --build --preset debug
```

## 构建 Application

进入工程目录：

```bash
cd application
```

Debug 配置和构建：

```bash
cmake --preset debug
cmake --build --preset debug
```

Release 配置和构建：

```bash
cmake --preset release
cmake --build --preset release
```

完成首次配置后，日常增量构建只需执行：

```bash
cmake --build --preset debug
```

## 构建产物

Bootloader：

```text
bootloader/build/bootloader.elf
bootloader/build/output/bootloader.bin
bootloader/build/output/bootloader.hex
```

Application：

```text
application/build/application.elf
application/build/output/application.bin
application/build/output/application.hex
```

`.elf` 用于调试和符号分析，`.hex` 与 `.bin` 用于烧录或生成升级包。

## Nvim / clangd

CMake 配置时会自动生成：

```text
bootloader/build/compile_commands.json
application/build/compile_commands.json
```

两个工程的 `.clangd` 已分别指向自己的 `build` 目录。首次打开源码前需完成对应工程的 CMake 配置；
新增源文件或头文件目录后也需要重新配置，以更新编译数据库。
Application 的 CMake 会将工具链检测到的目标 C 标准库目录写入编译参数，供 clangd 解析
FreeRTOS 等源码使用的 `stdlib.h`、`string.h`，无需硬编码本机路径。

重新配置 CMake 后如果 Nvim 仍显示旧诊断或 `gd` 无法跳转，可执行：

```vim
:checktime
:LspRestart
```

`:checktime` 用于检查磁盘上的外部修改；若缓冲区有未保存的编辑，先合并自己的修改，
不要强制重载。等待 clangd 完成索引后再尝试 `gd`。

## 清理构建结果

使用 CMake 清理当前配置生成的目标文件：

```bash
cmake --build --preset debug --target clean
```

同一工程的 Debug 和 Release 预设共用 `build` 目录，切换模式时先执行对应的配置命令。
