# Firmware 系统架构设计

## 0. 适用范围与当前假设

当前 Demo 工程按以下平台和工具链组织：

| 项目 | 当前选择 | 说明 |
| --- | --- | --- |
| MCU 系列 | STM32F1 | 以 STM32F1 系列为默认目标平台 |
| CPU 内核 | Cortex-M3 | 对应 FreeRTOS Cortex-M3 移植层 |
| 工具链 | GCC / arm-none-eabi-gcc | 当前 FreeRTOS 移植代码使用 GCC 版本 |
| FreeRTOS 移植层 | `portable/gcc/arm_cm3` | 适用于 Cortex-M3 + GCC |
| FreeRTOS 内存管理 | `portable/mem_mang/heap_4.c` | 默认使用 `heap_4` 动态内存管理 |
| 外设库 | STM32F1 HAL 或标准外设库二选一 | 当前目录同时预留，两者实际工程中只保留一种 |

后续平台或工具链变化时，优先修改以下位置：

- MCU 从 STM32F1 更换为其他系列：更新 `hardware/cmsis`、外设库目录、启动文件和链接脚本。
- CPU 内核从 Cortex-M3 更换为 Cortex-M0/M4/M33 等：替换 FreeRTOS 的 `portable` 移植层。
- 工具链从 GCC 更换为 Keil/IAR：替换 FreeRTOS 的 `portable/gcc/arm_cm3` 为对应工具链目录。
- Flash 分区变化：同步修改 Bootloader 与 Application 的 `core/flash_layout.h` 和链接脚本。
- 是否使用 HAL 或标准外设库：在 `hardware` 中保留实际使用的一种，删除或忽略另一种。

## 1. 设计目标与原则

本架构将 Bootloader 与 Application 设计为两个完全独立的工程，核心目标如下：

- **Bootloader 是一个完整且独立的工程。**
- **Application 是另一个完整且独立的工程。**
- 两个工程仅通过 Flash 地址、固定数据格式和升级协议进行交互。
- 两个工程不共享代码，避免产生编译和实现层面的耦合。

最终工程结构：

```text
demo
├── bootloader
│   ├── core
│   ├── app
│   ├── service
│   ├── middleware
│   └── hardware
└── application
    ├── core
    ├── app
    ├── service
    ├── middleware
    └── hardware
```

## 2. Bootloader 工程

### 2.1 工程定位

> 保持最小、稳定，尽量不随产品业务变化。

Bootloader 只负责系统启动和固件升级，不包含以下内容：

- FreeRTOS
- Modbus 业务
- 电机控制
- 具体设备逻辑

### 2.2 目录结构与职责

#### Core：芯片启动入口

主要职责：

- 系统上电
- 时钟初始化
- 最小必要硬件初始化

目录结构：

```text
core
├── main.c
├── startup
├── system_clock
└── linker
```

目录说明：

| 文件或目录 | 主要内容 |
| --- | --- |
| `main.c` | Bootloader 主入口和顶层初始化流程 |
| `startup` | 放置 `.s`/`.S` 启动汇编文件，包含中断向量表、复位入口和启动代码 |
| `system_clock` | 系统时钟配置 |
| `linker` | Bootloader 存储区域和段布局定义 |

依赖关系：

```text
startup → main.c → system_clock → app
```

#### App：启动流程编排

主要职责：

- 编排 Bootloader 整体运行流程
- 根据启动状态选择正常启动或固件升级
- 协调镜像检查、回滚和 Application 跳转

目录结构：

```text
app
└── boot_manager
```

目录说明：

| 子目录 | 主要内容 |
| --- | --- |
| `boot_manager` | 编排检查、选择、升级、回滚和跳转流程 |

典型启动流程：

```text
Reset
  ↓
boot_manager
  ↓
检查 Application 状态
  ↓
选择有效镜像
  ↓
jump_to_application
```

#### Service：启动与升级能力

主要职责：

- 检查 Application 镜像有效性
- 执行镜像跳转和失败回滚
- 管理固件接收、写入和升级状态

目录结构：

```text
service
├── app_check
├── app_jump
├── rollback
└── upgrade
```

目录说明：

| 子目录 | 主要内容 |
| --- | --- |
| `app_check` | 检查镜像头、地址、长度和有效性信息 |
| `app_jump` | 设置栈指针和向量表，并跳转至 Application |
| `rollback` | 记录启动结果，并在失败时切换至备用镜像 |
| `upgrade` | 管理固件接收、Flash 擦写和升级状态 |

代码归属判断：

- 与启动或升级业务能力有关的代码放入 `service`。
- 整体流程编排放入 `app`，不在 `service` 中组织跨模块流程。
- 协议解析和校验算法放入 `middleware`。

#### Middleware：通用组件

主要职责：

- 解析固件下载协议
- 校验固件格式和完整性
- 提供 CRC 等可复用算法

目录结构：

```text
middleware
├── protocol
├── firmware_check
└── crc
```

目录说明：

| 子目录 | 主要内容 |
| --- | --- |
| `protocol` | 解析下载命令、数据帧和响应信息 |
| `firmware_check` | 校验固件头、目标地址、版本和完整性 |
| `crc` | 提供 CRC 计算和比对能力 |

代码归属判断：

- 与具体通信接口无关的协议解析放入 `protocol`。
- UART、CAN 等通信收发接口放入 `hardware/bsp`。
- Middleware 不直接决定启动、升级或回滚流程。

依赖关系：

```text
app → service → middleware → hardware
```

#### Hardware：Bootloader 硬件层

主要职责：

- 封装 Bootloader 所需的硬件驱动
- 为启动和升级模块提供 Flash、通信及 GPIO 接口
- 隔离具体芯片和外设实现

目录结构：

```text
hardware
├── cmsis
├── stm32f1xx_hal_driver        # HAL 库（二选一）
├── stm32f10x_stdperiph_driver  # 标准外设库（二选一）
├── bsp
│   ├── flash
│   ├── uart
│   └── gpio
└── driver
    └── w25q128
```

目录说明：

| 子目录 | 对应对象 | 主要内容 |
| --- | --- | --- |
| `cmsis` | Cortex 内核与 MCU | 提供内核接口、寄存器定义和设备头文件 |
| `stm32f1xx_hal_driver` | STM32F1 HAL 库 | 提供 MCU 片上外设驱动，使用 HAL 库时保留 |
| `stm32f10x_stdperiph_driver` | STM32F1 标准外设库 | 提供 MCU 片上外设驱动，使用标准外设库时保留 |
| `bsp` | Bootloader 所需的板级资源 | 封装内部 Flash、UART、GPIO 等板级接口 |
| `driver` | 板载或外接器件 | 封装 W25Q128 等具体器件的控制协议 |

代码归属判断：

- 只保留启动和升级必需的硬件能力。
- HAL 库与标准外设库通常二选一。
- 与 MCU 片上外设及板卡资源有关的适配代码放入 `bsp`。
- 与具体器件型号及控制协议有关的代码放入 `driver`。
- 该目录属于 Bootloader，Application 不得直接引用。

#### Core 编译期配置

主要职责：

- 集中管理 Bootloader 版本信息
- 定义 Application 分区地址
- 维护 Flash 布局等编译期配置

目录结构：

```text
core
├── flash_layout.h
└── stm32f1xx_hal_conf.h
```

目录说明：

| 文件或目录 | 主要内容 |
| --- | --- |
| `flash_layout.h` | Bootloader 镜像地址和 Flash 分区大小 |
| `stm32f1xx_hal_conf.h` | Bootloader STM32F1 HAL 模块配置 |

配置文件直接放在 `core` 目录下，与使用它们的启动和芯片初始化代码放在一起。

主要配置项示例：

```c
BOOT_VERSION
APP_A_ADDRESS
APP_B_ADDRESS
FLASH_LAYOUT
```

## 3. Application 工程

### 3.1 工程定位

> 承载产品的全部业务功能。

### 3.2 目录结构与职责

#### Core：系统入口

主要职责：

- MCU 初始化
- 启动 FreeRTOS

目录结构：

```text
core
├── main.c
├── startup
├── system_clock
├── linker
├── system_init.c
├── rtos_start.c
└── rtos_start.h
```

目录说明：

| 文件或目录 | 主要内容 |
| --- | --- |
| `main.c` | Application 主入口和顶层启动流程 |
| `startup` | 放置 `.s`/`.S` 启动汇编文件，包含 Application 的中断向量表、复位入口和启动代码 |
| `system_clock` | Application 系统时钟配置 |
| `linker` | Application 存储区域和段布局定义，起始地址应与 Bootloader 分区规划一致 |
| `system_init.c` | 系统、板级资源和基础组件初始化 |
| `rtos_start.c` / `rtos_start.h` | 管理任务参数、创建 RTOS 对象并启动 FreeRTOS 调度器 |

依赖关系：

```text
main.c → system_init.c → rtos_start.c → App
```

#### App：产品业务流程

主要职责：

- 管理产品运行状态
- 编排跨设备的业务流程
- 处理产品级故障和状态切换

目录结构：

```text
app
├── device_manager
├── led
├── system_state
└── workflow
```

目录说明：

| 子目录 | 主要内容 |
| --- | --- |
| `device_manager` | 管理设备注册、运行状态和生命周期 |
| `led` | 编排 LED 开机闪烁流程和状态机 |
| `system_state` | 定义系统状态、事件和状态切换规则 |
| `workflow` | 编排制冷、除霜、自检等跨设备业务流程 |

依赖关系：

```text
core → app → service
```

业务示例：

在冰箱产品中可包含：

- 制冷状态
- 门状态
- 故障状态

#### Service：设备能力

主要职责：

- 封装电机、门、灯光等设备能力
- 向 `app` 提供稳定的业务接口
- 协调中间件和硬件层完成具体操作

目录结构：

```text
service
├── motor
├── door
├── led
├── temperature
└── alarm
```

目录说明：

| 子目录 | 对应能力 | 主要内容 |
| --- | --- | --- |
| `motor` | 电机 | 启停、转向、转速和运行状态控制 |
| `door` | 门体 | 开关状态检测和门锁控制 |
| `led` | LED | 提供开关和翻转等通用 LED 能力，不包含产品流程 |
| `temperature` | 温度 | 温度采集、转换和有效性判断 |
| `alarm` | 告警 | 告警产生、恢复和状态查询 |

代码归属判断：

- 单一设备对外提供的能力放入 `service`。
- 跨多个设备的流程编排放入 `app`。
- 寄存器、引脚和通信时序等细节放入 `hardware`。

接口示例：

```c
motor_start();
door_open();
light_on();
```

#### Middleware：通用组件

主要职责：

- 提供操作系统、通信、升级和日志等通用能力
- 屏蔽通用组件的实现细节
- 为 `service` 和 `app` 提供可复用接口

目录结构：

```text
middleware
├── freertos
│   ├── include
│   ├── source
│   └── portable
│       ├── gcc
│       │   └── arm_cm3
│       └── mem_mang
├── modbus
├── ota
├── log
└── console
```

目录说明：

| 子目录 | 主要内容 |
| --- | --- |
| `freertos` | 任务调度、同步和队列等操作系统能力 |
| `modbus` | 通信协议解析以及数据与业务命令之间的转换 |
| `ota` | 接收升级信息、写入升级标志并请求系统复位 |
| `log` | 日志分级、格式化和输出 |
| `console` | 调试命令注册、解析和执行 |

FreeRTOS 子目录说明：

| 子目录 | 主要内容 |
| --- | --- |
| `include` | FreeRTOS 公共头文件和接口声明 |
| `source` | 任务、队列、定时器和事件组等内核源码 |
| `portable/gcc/arm_cm3` | STM32F1/Cortex-M3 在 GCC 工具链下的移植代码 |
| `portable/mem_mang` | FreeRTOS 内存管理实现，当前使用 `heap_4.c` |

代码归属判断：

- 与具体产品业务无关、可被多个模块复用的组件放入 `middleware`。
- Middleware 不直接编排产品流程。
- OTA 只触发升级，复位后的固件校验和写入由 Bootloader 负责。

Modbus 数据流：

```text
rs485 → modbus → command
```

OTA 切换流程：

```text
application
    ↓
写入升级标志
    ↓
Reset
    ↓
bootloader 接管升级
```

#### Hardware：Application 硬件抽象层

主要职责：

- 封装 MCU 外设和板级硬件
- 向上层提供统一的硬件访问接口
- 隔离芯片、开发板和具体器件之间的差异

目录结构：

```text
hardware
├── cmsis
├── stm32f1xx_hal_driver        # HAL 库（二选一）
├── stm32f10x_stdperiph_driver  # 标准外设库（二选一）
├── bsp                         # 电路板资源定义与初始化
└── driver                      # 板载或外接器件驱动
```

目录说明：

| 子目录 | 对应对象 | 主要内容 | 示例 |
| --- | --- | --- | --- |
| `cmsis` | Cortex 内核与 MCU | 提供内核接口、寄存器定义和设备头文件 | Cortex-M3、STM32F1 设备头文件 |
| `stm32f1xx_hal_driver` | STM32F1 HAL 库 | 提供 MCU 片上外设驱动，使用 HAL 库时保留 | UART、SPI、I2C、ADC、GPIO |
| `stm32f10x_stdperiph_driver` | STM32F1 标准外设库 | 提供 MCU 片上外设驱动，使用标准外设库时保留 | USART、SPI、I2C、ADC、GPIO |
| `bsp` | 当前硬件板卡 | 定义引脚、通道和外设实例，并完成板级资源初始化 | LED 引脚、RS485 串口、蜂鸣器 PWM 通道、传感器供电控制 |
| `driver` | 板载或外接器件 | 基于 `bsp` 实现具体器件的控制协议 | W25Q128、温度传感器、显示屏、电机驱动芯片 |

代码归属判断：

- CMSIS、HAL 库或标准外设库直接放入 `hardware`。
- HAL 库与标准外设库通常二选一。
- 与 MCU 片上外设、原理图、PCB 引脚或板卡版本有关的适配代码放入 `bsp`。
- 与具体器件型号及其通信协议有关的代码放入 `driver`。

推荐依赖方向：

```text
service / middleware
        ↓
Driver / BSP
        ↓
MCU
```

例如，读取板载温度传感器时：

```text
temperature_service
        ↓
temperature_sensor_driver
        ↓
Board I2C 配置（BSP）
```

#### Core 编译期配置

主要职责：

- 管理板级配置
- 管理产品和设备参数
- 维护 Application 版本信息

目录结构：

```text
core
├── FreeRTOSConfig.h
├── flash_layout.h
└── stm32f1xx_hal_conf.h
```

目录说明：

| 文件或目录 | 主要内容 |
| --- | --- |
| `FreeRTOSConfig.h` | FreeRTOS 内核编译期配置 |
| `flash_layout.h` | Application 起始地址和 Flash 分区大小 |
| `stm32f1xx_hal_conf.h` | Application STM32F1 HAL 模块配置 |

编译期配置文件直接放在 `core` 目录下，与系统启动代码放在一起。

代码归属判断：

- 硬件板卡差异由 `core` 下的板级配置文件管理。
- 产品型号和业务参数差异由 `core` 下的设备配置文件管理。
- 运行过程中需要持久化的参数应由专门的存储模块管理，不直接写在编译期配置中。

## 4. 工程间交互契约

Bootloader 与 Application 不共享代码，只通过明确、稳定的协议约定交互。

### 4.1 Flash 数据协议

当前 STM32F103RCT6 工程约定的 Boot Info 地址为：

```text
0x0803F800
```

该地址可用于存放启动和升级信息：

```c
typedef struct
{
    uint32_t upgrade_flag;
    uint32_t image_size;
    uint32_t image_crc;
    uint32_t version;
} boot_info_t;
```

`boot_info_t` 由两个工程分别定义并维护。双方必须保证以下内容完全一致：

- 字段含义
- 字段类型与长度
- 字段顺序
- 字节序与对齐方式
- 数据版本及兼容策略

数据格式一致并不代表共享代码；两个工程在源码和构建层面仍保持独立。

### 4.2 固件文件格式

双方约定统一的升级包格式：

```text
firmware.bin
+----------------+
| Header         |
+----------------+
| Application    |
| Data           |
+----------------+
| CRC            |
+----------------+
```

- Application 构建系统负责生成符合约定的固件包。
- Bootloader 负责解析、写入并校验固件包。

## 5. 依赖关系与边界

### 5.1 Bootloader 依赖方向

```text
core
  ↓
app
  ↓
service
  ↓
middleware
  ↓
hardware
  ↓
MCU
```

### 5.2 Application 依赖方向

```text
core
  ↓
app
  ↓
service
  ↓
middleware
  ↓
hardware
  ↓
MCU
```

### 5.3 工程边界

两个工程之间不存在源码依赖：

```text
bootloader  ──X──> application
application ──X──> bootloader
```

双方仅依赖第 4 节定义的交互契约。

## 6. Flash 布局

### 6.1 STM32F103RCT6 当前分区

STM32F103RCT6 包含 256 KiB 内部 Flash、48 KiB SRAM，Flash 擦除页大小为 2 KiB。当前分区如下：

| 区域 | 起始地址 | 结束地址（不含） | 大小 |
| --- | --- | --- | --- |
| Bootloader | `0x08000000` | `0x08008000` | 32 KiB |
| Application | `0x08008000` | `0x0803F800` | 222 KiB |
| Boot Info | `0x0803F800` | `0x08040000` | 2 KiB |

Boot Info 独占一个擦除页，更新升级标志时不会擦除 Application。该区域适合保存带版本的数据结构和低频更新的启动、升级元数据，不适合保存频繁变化的运行参数。

STM32F103RCT6 内部 Flash 无法同时容纳两个完整的 222 KiB Application 分区。需要保留完整备用镜像时，应将升级包放入 W25Q128 等外部 Flash，由 Bootloader 校验并更新内部 Application。

### 6.2 分区配置位置

Bootloader 与 Application 分别维护自己的分区定义：

- `demo/bootloader/core/flash_layout.h`
- `demo/application/core/flash_layout.h`

这种重复是有意设计的，用于保持两个工程之间无源码依赖。修改分区时必须同步更新两份定义，并保证字段含义、地址和大小一致。

对应的链接脚本位于：

- `demo/bootloader/core/linker/bootloader.ld`
- `demo/application/core/linker/application.ld`
- 两个工程各自的 `core/linker/stm32f103rct_reference.ld`

Application 在 `demo/application/core/system_clock/system_stm32f1xx.c` 中根据 `APP_FLASH_ORIGIN` 设置向量表地址。Bootloader 后续的镜像检查和跳转实现也必须使用 `APP_FLASH_ORIGIN`，不得另外硬编码地址。

### 6.3 修改分区后的检查项

修改 Flash 布局后必须检查：

1. 所有区域的起始地址和大小符合芯片 Flash 页或扇区的擦除粒度。
2. 各区域互不重叠，末地址不超过芯片 Flash 范围。
3. Application 起始地址符合目标内核的向量表对齐要求。
4. 两份 `flash_layout.h` 与两个链接脚本中的地址保持一致。
5. Bootloader 跳转前根据目标芯片 SRAM 范围检查 Application 初始栈指针。
6. Bootloader 从 `APP_FLASH_ORIGIN + 4` 读取 Application Reset Handler。
7. 重新构建两个工程，并执行以下命令确认 `.isr_vector` 地址：

```bash
arm-none-eabi-objdump -h build/bootloader/bootloader.elf
arm-none-eabi-objdump -h build/application/application.elf
```

STM32F103RCT6 当前预期结果：

```text
bootloader  .isr_vector = 0x08000000
application .isr_vector = 0x08008000
```

### 6.4 迁移到 STM32F407ZGT6 的示例

STM32F407ZGT6 是 Cortex-M4F 芯片，具有 1 MiB Flash、128 KiB SRAM，并使用非均匀 Flash 扇区。不能只修改 Flash 总容量。

一个便于擦除管理的示例分区为：

| 区域 | 起始地址 | 结束地址（不含） | 大小 | F407 扇区 |
| --- | --- | --- | --- | --- |
| Bootloader | `0x08000000` | `0x08020000` | 128 KiB | 0～4 |
| Application | `0x08020000` | `0x080E0000` | 768 KiB | 5～10 |
| Boot Info | `0x080E0000` | `0x08100000` | 128 KiB | 11 |

该方案为 Boot Info 保留完整扇区，确保擦除元数据时不会损坏 Application。如果认为 128 KiB 的元数据扇区开销过大，需要重新设计存储策略，不能把元数据直接放进包含 Application 代码的擦除扇区。

迁移到 STM32F407ZGT6 时必须同步完成：

- 将 STM32F1 CMSIS Device 替换为 STM32F4 CMSIS Device。
- 将 STM32F1 HAL 替换为 `STM32F4xx_HAL_Driver` 及对应 HAL 配置。
- 将 `startup_stm32f103xe.s` 替换为 `startup_stm32f407xx.s`。
- 将两个链接脚本替换为 STM32F407ZGT6 的 Flash 和 SRAM 布局。
- 将芯片宏从 `STM32F103xE` 改为 `STM32F407xx`。
- 将编译参数改为 Cortex-M4F，例如：

```text
-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
```

- 将 FreeRTOS `arm_cm3` 移植层替换为匹配的 Cortex-M4F 移植层。
- 替换系统时钟、GPIO/MSP、中断文件和 BSP 引脚配置。
- 将 Bootloader Flash 擦写实现改为 STM32F407 的扇区擦除方式。
- 按 STM32F407ZGT6 的 SRAM 地址范围更新 Application 初始栈指针检查。

不得在 STM32F407 工程中继续使用 STM32F103 的启动文件、链接脚本、Flash 页擦除实现或 FreeRTOS Cortex-M3 移植层。

## 7. 架构优势

### 7.1 安全性

Application 的升级和业务变更不会直接修改 Bootloader，降低启动程序被破坏的风险。

### 7.2 可维护性

业务组件变更只影响 Application。例如修改 Modbus 功能时，无需修改或重新发布 Bootloader。

### 7.3 便于认证和版本管理

Bootloader 可以长期保持固定、已验证的版本，Application 则根据产品需求独立迭代。

### 7.4 便于平台移植

当 MCU 从 STM32 更换为 GD32 等其他平台时，主要调整以下目录：

```text
bootloader/hardware
application/hardware
```

`hardware` 负责 MCU 适配、板卡及器件实现，上层启动逻辑和产品业务可尽量保持不变。
