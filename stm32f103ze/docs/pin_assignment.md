# STM32F103ZE 引脚分配表

本文记录 LQFP144 封装在当前固件中的 GPIO 引脚分配。表格按 PA0、PA1……的顺序排列，仅列出该封装实际引出的 GPIO。

- “功能”为空表示当前仓库固件未分配该引脚，不表示芯片不支持该引脚或其复用功能。
- UART2～UART5 按代码中已有的候选映射列出，不跟随当前启用开关变化。
- 工程在 HAL 初始化时关闭 JTAG 并保留 SWD；PA13、PA14 保留为调试口，其余未分配引脚初始化为模拟模式、无上下拉。
- 本表描述固件分配，不替代原理图、电气约束及芯片数据手册。

| 引脚 | 功能 | 作用 | 使用范围 |
| --- | --- | --- | --- |
| PA0 |  |  |  |
| PA1 |  |  |  |
| PA2 | USART2_TX | 串口 2 发送 | Application |
| PA3 | USART2_RX | 串口 2 接收 | Application |
| PA4 |  |  |  |
| PA5 | STATUS_LED | 低电平点亮；用于启动指示、运行状态闪烁和故障安全熄灭 | Bootloader / Application |
| PA6 |  |  |  |
| PA7 |  |  |  |
| PA8 |  |  |  |
| PA9 | USART1_TX | 115200-8-N-1 调试日志发送 | Application |
| PA10 | USART1_RX | 115200-8-N-1 调试串口接收 | Application |
| PA11 |  |  |  |
| PA12 |  |  |  |
| PA13 | SWDIO | SWD 调试与程序下载数据线 | Bootloader / Application |
| PA14 | SWCLK | SWD 调试与程序下载时钟线 | Bootloader / Application |
| PA15 |  |  |  |
| PB0 |  |  |  |
| PB1 |  |  |  |
| PB2 |  |  |  |
| PB3 |  |  |  |
| PB4 |  |  |  |
| PB5 |  |  |  |
| PB6 |  |  |  |
| PB7 |  |  |  |
| PB8 |  |  |  |
| PB9 |  |  |  |
| PB10 | USART3_TX | 串口 3 发送 | Application |
| PB11 | USART3_RX | 串口 3 接收 | Application |
| PB12 |  |  |  |
| PB13 |  |  |  |
| PB14 |  |  |  |
| PB15 |  |  |  |
| PC0 |  |  |  |
| PC1 |  |  |  |
| PC2 |  |  |  |
| PC3 |  |  |  |
| PC4 |  |  |  |
| PC5 |  |  |  |
| PC6 |  |  |  |
| PC7 |  |  |  |
| PC8 |  |  |  |
| PC9 |  |  |  |
| PC10 | UART4_TX | 串口 4 发送 | Application |
| PC11 | UART4_RX | 串口 4 接收 | Application |
| PC12 | UART5_TX | 串口 5 发送 | Application |
| PC13 |  |  |  |
| PC14 |  |  |  |
| PC15 |  |  |  |
| PD0 | OSC_IN | 8 MHz HSE 晶振/外部时钟输入，作为系统 PLL 时钟源 | Bootloader / Application |
| PD1 | OSC_OUT | HSE 晶振输出 | Bootloader / Application |
| PD2 | UART5_RX | 串口 5 接收 | Application |
| PD3 |  |  |  |
| PD4 |  |  |  |
| PD5 |  |  |  |
| PD6 |  |  |  |
| PD7 |  |  |  |
| PD8 |  |  |  |
| PD9 |  |  |  |
| PD10 |  |  |  |
| PD11 |  |  |  |
| PD12 |  |  |  |
| PD13 |  |  |  |
| PD14 |  |  |  |
| PD15 |  |  |  |
| PE0 |  |  |  |
| PE1 |  |  |  |
| PE2 |  |  |  |
| PE3 |  |  |  |
| PE4 |  |  |  |
| PE5 |  |  |  |
| PE6 |  |  |  |
| PE7 |  |  |  |
| PE8 |  |  |  |
| PE9 |  |  |  |
| PE10 |  |  |  |
| PE11 |  |  |  |
| PE12 |  |  |  |
| PE13 |  |  |  |
| PE14 |  |  |  |
| PE15 |  |  |  |
| PF0 |  |  |  |
| PF1 |  |  |  |
| PF2 |  |  |  |
| PF3 |  |  |  |
| PF4 |  |  |  |
| PF5 |  |  |  |
| PF6 |  |  |  |
| PF7 |  |  |  |
| PF8 |  |  |  |
| PF9 |  |  |  |
| PF10 |  |  |  |
| PF11 |  |  |  |
| PF12 |  |  |  |
| PF13 |  |  |  |
| PF14 |  |  |  |
| PF15 |  |  |  |
| PG0 |  |  |  |
| PG1 |  |  |  |
| PG2 |  |  |  |
| PG3 |  |  |  |
| PG4 |  |  |  |
| PG5 |  |  |  |
| PG6 |  |  |  |
| PG7 |  |  |  |
| PG8 |  |  |  |
| PG9 |  |  |  |
| PG10 |  |  |  |
| PG11 |  |  |  |
| PG12 |  |  |  |
| PG13 |  |  |  |
| PG14 |  |  |  |
| PG15 |  |  |  |

## 维护依据

引脚配置以当前源码为准，修改下列配置时应同步更新本表：

- GPIO：`application/hardware/bsp/gpio/bsp_gpio.c` 与 `bootloader/hardware/bsp/gpio/bsp_gpio.c` 中对应物理引脚的独立配置宏
- UART：`application/hardware/bsp/uart/bsp_uart.h`
- HSE：`application/core/system_clock/system_clock.c` 与 `bootloader/core/system_clock/system_clock.c`
