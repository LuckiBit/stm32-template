# STM32F429IG 引脚分配表

本文记录 LQFP176 封装在当前固件中的 GPIO 引脚分配。表格按 PA0、PA1……的顺序排列，仅列出该封装实际引出的 GPIO。

- “功能”为空表示当前仓库固件未分配该引脚，不表示芯片不支持该引脚或其复用功能。
- UART2～UART5 按代码中已有的候选映射列出，不跟随当前启用开关变化。
- JTAG/SWD 项保留芯片复位后的默认调试功能；除 HSE、调试口和已分配引脚外，其余引脚初始化为模拟模式、无上下拉。
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
| PA13 | JTMS / SWDIO | JTAG/SWD 调试与程序下载数据线 | Bootloader / Application |
| PA14 | JTCK / SWCLK | JTAG/SWD 调试与程序下载时钟线 | Bootloader / Application |
| PA15 | JTDI | JTAG 调试数据输入；切换为仅 SWD 后可释放 | Bootloader / Application |
| PB0 |  |  |  |
| PB1 |  |  |  |
| PB2 |  |  |  |
| PB3 | JTDO / TRACESWO | JTAG 数据输出或 SWO 跟踪；切换为仅 SWD 后可释放 | Bootloader / Application |
| PB4 | NJTRST | JTAG 复位；切换为仅 SWD 后可释放 | Bootloader / Application |
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
| PD0 |  |  |  |
| PD1 |  |  |  |
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
| PH0 | OSC_IN | 25 MHz HSE 晶振/外部时钟输入，作为系统 PLL 时钟源 | Bootloader / Application |
| PH1 | OSC_OUT | HSE 晶振输出 | Bootloader / Application |
| PH2 |  |  |  |
| PH3 |  |  |  |
| PH4 |  |  |  |
| PH5 |  |  |  |
| PH6 |  |  |  |
| PH7 |  |  |  |
| PH8 |  |  |  |
| PH9 |  |  |  |
| PH10 |  |  |  |
| PH11 |  |  |  |
| PH12 |  |  |  |
| PH13 |  |  |  |
| PH14 |  |  |  |
| PH15 |  |  |  |
| PI0 |  |  |  |
| PI1 |  |  |  |
| PI2 |  |  |  |
| PI3 |  |  |  |
| PI4 |  |  |  |
| PI5 |  |  |  |
| PI6 |  |  |  |
| PI7 |  |  |  |
| PI8 |  |  |  |
| PI9 |  |  |  |
| PI10 |  |  |  |
| PI11 |  |  |  |

## 维护依据

引脚配置以当前源码为准，修改下列配置时应同步更新本表：

- GPIO：`application/hardware/bsp/gpio/bsp_gpio.c` 与 `bootloader/hardware/bsp/gpio/bsp_gpio.c` 中对应物理引脚的独立配置宏
- UART：`application/hardware/bsp/uart/bsp_uart.h`
- HSE：`application/core/system_clock/system_clock.c` 与 `bootloader/core/system_clock/system_clock.c`
