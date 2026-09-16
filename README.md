# STM32 固件工程模板

本仓库按芯片型号维护相互独立的固件工程：

- [`stm32f103rc`](stm32f103rc/README.md)：STM32F103RC 专属工程。
- [`stm32f103ze`](stm32f103ze/README.md)：STM32F103ZE 专属工程。
- [`stm32f103c8`](stm32f103c8/README.md)：STM32F103C8 专属工程。
- [`stm32f429ig`](stm32f429ig/README.md)：STM32F429IG 专属工程。

每个目录都包含完整的 Bootloader、Application、构建配置和项目文档，
并且只使用对应芯片的链接脚本。具体架构、外设配置、构建方法和烧录产物请查看各工程目录中的 `README.md`。

各工程均使用 CMake、Ninja 和 `arm-none-eabi-gcc` 构建。

## 许可证

本仓库中的所有工程统一使用根目录的 [LICENSE](LICENSE)。
