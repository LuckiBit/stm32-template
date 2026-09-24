# Firmware 系统架构

本文描述当前源码与 CMake 实际构建的架构。运行期细节见
[RTOS 启动架构](rtos_startup.md)，代码约定见 [C 语言编码规范](c_coding_standard.md)。

## 1. 当前平台与工程边界

| 项目 | 当前实现 |
| --- | --- |
| 目标芯片 | STM32F103ZET6，Cortex-M3，512 KiB Flash、64 KiB SRAM |
| 编译工具链 | GCC `arm-none-eabi-gcc`，C11，CMake、Ninja |
| 编译告警 | 两个工程均启用 `-Wall -Wextra` |
| 外设驱动 | 两个工程均编译 STM32F1 HAL，芯片宏为 `STM32F103xE` |
| Application RTOS | FreeRTOS，GCC `arm_cm3` 移植层，单核抢占调度 |
| RTOS 内存 | 仅为启用对象静态分配，不链接 `heap_4.c` |
| Bootloader | 裸机运行，不使用 FreeRTOS |

仓库包含 `bootloader` 和 `application` 两个独立工程，各有自己的源码、芯片支持文件、
链接脚本、CMake 配置和编译数据库。两个工程不互相引用源码。

当前 Bootloader 已实现 Application 向量表检查及跳转；升级接收、完整镜像校验、回滚
尚未实现。Application 已实现固定 RTOS 资源创建、启动就绪协调、LED 示例及故障停机。

## 2. 五层结构与当前目录

两个固件工程的源码固定使用 `app`、`core`、`hardware`、`service`、`middleware` 五层。
`cmake` 是构建工具目录，`build` 是生成目录，仓库根目录的 `docs` 是文档目录，均不属于源码层。

下面列出当前参与构建的主要文件；同名 `.h` 接口文件与 `.c` 文件放在同一目录。

```text
stm32-template/
├── README.md
├── docs/
│   ├── firmware_arch.md
│   ├── rtos_startup.md
│   └── c_coding_standard.md
├── bootloader/
│   ├── app/
│   │   └── led/led.c
│   ├── core/
│   │   ├── main.c
│   │   ├── system_init.c
│   │   ├── application_boot.c
│   │   ├── flash_layout.h
│   │   ├── stm32f1xx_it.c
│   │   ├── stm32f1xx_hal_conf.h
│   │   ├── startup/startup_stm32f103xe.s
│   │   ├── system_clock/
│   │   └── linker/
│   ├── hardware/
│   │   ├── bsp/
│   │   │   ├── gpio/bsp_gpio.c
│   │   │   └── uart/bsp_uart.c
│   │   ├── cmsis/
│   │   └── stm32f1xx_hal_driver/
│   ├── service/
│   │   ├── led/led_service.c
│   │   ├── my_printf/
│   │   └── time/delay_service.c
│   ├── middleware/
│   │   └── nanoprintf/
│   ├── cmake/gcc-arm-none-eabi.cmake
│   ├── CMakeLists.txt
│   └── CMakePresets.json
└── application/
    ├── app/
    │   ├── system_manager/system_manager.c
    │   ├── tasks/tasks.c
    │   └── led/led.c
    ├── core/
    │   ├── main.c
    │   ├── system_init.c
    │   ├── rtos_start.c
    │   ├── rtos_fault.c
    │   ├── FreeRTOSConfig.h
    │   ├── flash_layout.h
    │   ├── stm32f1xx_it.c
    │   ├── stm32f1xx_hal_conf.h
    │   ├── startup/startup_stm32f103xe.s
    │   ├── system_clock/
    │   └── linker/
    ├── hardware/
    │   ├── bsp/
    │   │   ├── gpio/bsp_gpio.c
    │   │   └── uart/bsp_uart.c
    │   ├── cmsis/
    │   └── stm32f1xx_hal_driver/
    ├── service/
    │   ├── led/led_service.c
    │   └── my_printf/
    ├── middleware/
    │   ├── freertos/
    │   └── nanoprintf/
    ├── cmake/gcc-arm-none-eabi.cmake
    ├── CMakeLists.txt
    └── CMakePresets.json
```

### 2.1 分层职责

| 层 | 职责 | 当前示例 |
| --- | --- | --- |
| `core` | 芯片启动、时钟、中断、链接与编译期配置；连接应用入口和底层终止路径 | `system_init`、`application_boot`、`rtos_start`、`rtos_fault` |
| `app` | 应用流程、启动策略、任务入口、业务状态机和资源生命周期 | `system_manager`、`tasks`、`led` |
| `service` | 可供应用使用的设备能力 | LED 控制；Bootloader 的阻塞延时 |
| `middleware` | 操作系统及通用组件 | FreeRTOS 内核与移植层 |
| `hardware` | CMSIS、HAL、板级资源和具体器件驱动 | 通用 GPIO 引脚、未使用引脚管理、Application 串口、芯片支持代码 |

`system_manager` 决定何时放行业务以及故障后如何处理，因此属于 `app`。
它的名字不代表该模块负责芯片启动。`core/rtos_start.c` 负责创建入口和启动调度器，
业务初始化期间的协调由 `app/system_manager` 完成。

分层不是每次调用都必须逐层经过的固定链条。当前 `app` 直接使用 FreeRTOS，
LED 服务直接调用 BSP；`core` 为启动和致命故障处理调用应用或硬件接口。

### 2.2 预留模块与已实现模块的区别

工作区中可能保留以下空目录，它们不是已实现的产品功能，也未加入当前 CMake 源文件列表。
空目录不会由 Git 自动保存，应以实际源码及 CMake 列表判断模块是否存在。

| 工程 | 预留位置 |
| --- | --- |
| Bootloader | `app/boot_manager`；`service/app_check`、`app_jump`、`rollback`、`upgrade`；`middleware/crc`、`firmware_check`、`protocol` |
| Application | `app/device_manager`、`system_state`、`workflow`；`service/alarm`、`door`、`motor`、`temperature`；`middleware/console`、`log`、`modbus`、`ota` |
| 两个工程 | `hardware/driver`、`hardware/stm32f10x_stdperiph_driver` 等扩展位置 |

新增业务在现有五层内部增加模块。当前 `tasks` 中的数字编号用于资源预留，
不代表对应通信协议、执行器或设备功能已经实现。

## 3. Bootloader 当前启动流程

实现位置：[`main.c`](../bootloader/core/main.c)、
[`application_boot.c`](../bootloader/core/application_boot.c)。

```text
Reset_Handler → SystemInit → main
    ↓
system_init：HAL、时钟、GPIO、UART 初始化
    ↓
system_info_print：输出 Bootloader 版本、芯片、主频、Flash/RAM 占用与构建类型
    ↓
led_run：每隔 100 ms 翻转 LED，共 4 次
    ↓
application_is_valid：读取 Application 的前两个向量项
    ├─ 无效：循环执行 LED 流程，留在 Bootloader
    └─ 有效：led_stop → application_start
                            ↓
                      跳转到 Application Reset_Handler
```

`application_is_valid()` 当前检查：初始栈指针位于配置的 SRAM 范围内并满足 8 字节对齐；
复位入口去除 Thumb 标志后位于 Application 分区内，且 Thumb 标志有效。
这只是向量项的基本有效性检查，不是固件内容 CRC、签名或完整性验证。

`application_start()` 屏蔽中断，停止 SysTick，禁用并清除当前实现使用的 NVIC 中断组，
将 `SCB->VTOR` 设置为 `APP_START_ADDRESS`，再设置 MSP、开启中断并跳转到复位入口。
Application 重新执行自己的启动代码和硬件初始化。

当前检查和跳转实现在 `core/application_boot.c`，不能把预留的 `service/app_check`
和 `service/app_jump` 写成当前执行路径。Bootloader 没有升级任务或 RTOS 后台任务。

Bootloader 使用 `service/my_printf` 的单线程裸机实现，经 `middleware/nanoprintf` 格式化后
调用 `hardware/bsp/uart` 轮询发送；启动信息打印完成后再检查并跳转 Application。

## 4. Application 当前启动与运行

`system_init()` 完成 HAL、时钟、GPIO 和已启用串口初始化后进入 RTOS 启动流程。
`hardware/bsp/uart` 在 `bsp_uart.h` 为 5 路串口分别提供使能、波特率、字长、停止位、
校验、收发模式、流控和过采样配置；各路初始化独立读取，默认均为 TX/RX、115200、8N1 和无硬件流控，
引脚、GPIO 时钟和 USART 重映射配置同样集中在 `bsp_uart.h`，
由 `bsp_uart.c` 中的 `HAL_UART_MspInit()` 配置外设时钟和引脚；
公共 `stm32f1xx_hal_msp.c` 负责全局 MSP 初始化。当前仅启用串口 1（PA9 TX、PA10 RX），
不启用串口中断或 DMA，也未重定向 libc `printf`。`service/my_printf` 使用 nanoprintf
格式化到固定局部缓冲区，再依次通过所有已启用输出串口整块发送；默认仅输出到串口 1，
服务自持静态互斥量串行化多任务发送。

实现位置：[`rtos_start.c`](../application/core/rtos_start.c)、
[`system_manager.c`](../application/app/system_manager/system_manager.c)、
[`tasks.c`](../application/app/tasks/tasks.c)。

```text
Reset_Handler → SystemInit → main → system_init
    ↓
rtos_start
    ├─ system_manager_create(tasks_start, REQUIRED_TASKS)
    ├─ tasks_create()：仅创建启用项
    └─ vTaskStartScheduler()
                ↓
      system 管理任务：INITIALIZING
                ↓
      已启用的 task_n 各自报告就绪并等待许可
                ↓
      全部就绪 → 调用 tasks_start → RUNNING → 统一放行
                ↓
      业务运行；system 常驻等待故障事件
```

`core/rtos_start.c` 注入 `tasks_start` 回调和必要任务位图。
`system_manager` 不直接包含 `tasks.h`，通过回调启动业务模块的服务；
`tasks` 调用管理模块的就绪和许可接口，避免两个模块相互包含对方的接口。

`app/tasks/tasks.h` 定义编译期开关，`REQUIRED_TASKS` 由开关自动计算。
只等待启用项，就绪等待有 5000 ms 的总截止时间；分批报告不会重置计时。
`rtos_start()` 使用 C11 `_Noreturn` 声明：正常调度不会返回，意外返回会进入故障停机。

### 4.1 任务和对象配置

保留 16 个业务任务槽位，默认只创建 LED 的 `task_4`。
正常启动后共 **3 个任务**：`task_4`、`system`、FreeRTOS 空闲任务。
软件定时器服务按需创建；全部 16 个业务任务开启时，包括管理器和两个内核任务共 19 个。
全部业务关闭时只有管理器和空闲任务，空就绪集合允许直接进入服务启动。

| 对象 | 业务模块槽位 | 默认创建数 |
| --- | ---: | ---: |
| 业务任务 | 16 | 1 |
| 消息队列 | 8 | 0 |
| 二值信号量 | 8 | 0 |
| 互斥量 | 8 | 0 |
| 业务事件组 | 4 | 0 |
| 软件定时器 | 4 | 0 |

管理器内部事件组始终存在。内核定时器命令队列只在定时器服务开启时创建，
不计入业务队列槽位。禁用项的静态存储、句柄、创建及函数代码一起通过条件编译排除。

`TASK_n_ENABLE` 等开关集中在 `app/tasks/tasks.h`，默认仅 `TASK_4_ENABLE=1`。
开启 `task_0`、`task_1` 时，默认依赖自动启用对应定时器和事件组。
启用的预留任务在放行后阻塞等待通知；编号本身不意味着业务已经实现。
配套资源可独立选择，配置检查会拒绝当前事件示例的依赖缺失。

详细开关、依赖、任务优先级、栈容量和扩展方法见 [RTOS 启动架构](rtos_startup.md)。

### 4.2 当前模块调用关系

```text
core/main → core/system_init → 时钟、HAL、BSP
         └→ core/rtos_start → app/system_manager
                           └→ app/tasks

app/system_manager ──启动回调──→ tasks_start
app/tasks → system_manager_report_ready / system_manager_wait_running
app/tasks.task_4 → app/led → service/led → hardware/bsp/gpio
core/rtos_start → service/my_printf（创建静态互斥量）
service/my_printf → middleware/nanoprintf、hardware/bsp/uart、middleware/freertos
app/system_manager、app/tasks、app/led → middleware/freertos
致命 RTOS 故障 → core/rtos_fault → hardware/bsp/gpio
```

LED 任务使用单一的 500 ms 周期，每个周期翻转一次输出电平。GPIO BSP 使用明确的物理引脚标识，BSP_GPIOA_5 对应 PA5；
封装实际引出的每个 GPIO 都有独立的端口、引脚、初始化开关、模式、上下拉、速度、初始电平和安全电平宏；
修改引脚用途时只需修改对应引脚的配置宏。LED Service 负责低电平有效的设备语义。未使用 GPIO
默认初始化为模拟模式、无上下拉；HSE 和调试引脚保留独立配置块，但默认关闭 GPIO 初始化。

### 4.3 内存和故障边界

FreeRTOS 配置允许静态分配、禁用动态分配；任务、队列、信号量、事件组和定时器均由
模块按启用开关持有静态存储。内核为空闲任务及按需启用的定时器任务提供静态存储，
构建不包含 `heap_4.c`。
链接脚本仍保留 C 运行库堆和主栈的最小空间，这与 RTOS 对象静态分配并不冲突。

`rtos_fault_stop()` 保存首个 `g_rtos_fault`，屏蔽可屏蔽中断、关闭 LED 并停止执行。
它不依赖日志任务、队列或堆；记录不跨复位保存。
管理任务尚未实现自动恢复、降级、看门狗或持续健康监测。芯片异常处理和时钟初始化错误
仍走各自原有路径，并非所有故障都进入 `rtos_fault_stop()`。

## 5. Flash 布局与两个工程的契约

以下结束地址均不包含在分区内：

| 分区 | 起始地址 | 结束地址 | 大小 |
| --- | --- | --- | --- |
| Bootloader | `0x08000000` | `0x08008000` | 32 KiB |
| Application | `0x08008000` | `0x0807F800` | 478 KiB |
| Boot Info | `0x0807F800` | `0x08080000` | 2 KiB，独占一个擦除页 |

SRAM 范围为 `0x20000000`～`0x20010000`，容量 64 KiB。

配置位置：

- [Bootloader 分区常量](../bootloader/core/flash_layout.h)。
- [Application 分区常量](../application/core/flash_layout.h)。
- [Bootloader 链接布局](../bootloader/core/linker/stm32f103ze.ld)。
- [Application 链接布局](../application/core/linker/stm32f103ze.ld)。

两个工程的 `core/linker/` 均只保存 ZE 对应的链接脚本，CMake 直接引用该脚本。

两份 `flash_layout.h` 分别维护，修改分区时必须同步，链接脚本的数值也必须一致。
Bootloader 检查和跳转使用 `APP_START_ADDRESS`；Application 的
[`SystemInit`](../application/core/system_clock/system_stm32f1xx.c) 也使用该宏设置向量表。
初始栈指针位于 Application 起始地址，复位入口位于其后一个 `uint32_t`。

Boot Info 目前只有预留地址，源码尚未定义并读写升级元数据结构。
当前构建输出原始 `.bin`、`.hex` 和 `.elf`，没有额外封装带镜像头、版本和 CRC 的升级包。
后续实现升级协议时，需要在两个工程之间明确字段、字节序、长度、版本、校验和掉电处理契约。

## 6. 构建、编辑器与验证

构建和 Nvim 使用方法以 [README](../README.md) 为入口。
两个工程各自提供 `debug`、`release` 预设；同一工程的两个预设共用其 `build` 目录，
切换模式时要重新配置。

在仓库根目录验证链接向量地址：

```bash
arm-none-eabi-objdump -h bootloader/build/bootloader.elf
arm-none-eabi-objdump -h application/build/application.elf
```

`.isr_vector` 预期分别位于 `0x08000000` 和 `0x08008000`。
更改分区后，还需检查页面对齐、区域边界、两份常量与链接布局、向量入口和跳转行为。

新增模块时将文件列入对应工程的 `CMakeLists.txt`，公开接口目录列入 include 路径，
然后重新配置以更新 `compile_commands.json`。`.clangd` 分别指向各自的 `build`。
Application 的 CMake 将编译器检测到的目标 C 标准库路径导出到编译参数，支持 clangd
解析 FreeRTOS 的标准库依赖。

格式使用两个工程已有的 `.clang-format`，不为架构调整修改格式配置。
验证按改动范围执行构建、静态检查和板上检查，不额外增加源码层级。
构建成功仅说明编译链接通过，不表示 Bootloader 跳转、调度时序或硬件故障行为已经上板验证。

## 7. 后续模块与平台迁移

产品功能继续放在五层内部：流程协调属于 `app`，可复用设备能力属于 `service`，
协议或通用算法属于 `middleware`，板级和具体器件适配属于 `hardware`。
实现时更新实际源码、CMake 列表与本文的已实现状态。

迁移芯片或工具链需要同时核对 CMSIS、HAL、芯片宏、启动向量、时钟、BSP、编译参数、
FreeRTOS 移植层以及两套链接脚本和分区常量。当前只配置了 STM32F103ZET6，
不能仅修改容量数字就把该工程视为支持其他 MCU。
