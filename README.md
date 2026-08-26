# STM32 固件工程模板

仓库根目录包含两个相互独立的固件工程：

- `bootloader`：系统启动与固件升级。
- `application`：FreeRTOS 与产品业务功能。

两个工程都使用 CMake、Ninja 和 `arm-none-eabi-gcc` 构建，并分别提供自己的 `CMakePresets.json`。

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

两个工程的 `.clangd` 已分别指向自己的 `build` 目录。重新配置 CMake 后如果 Nvim 没有更新索引，可执行：

```vim
:LspRestart
```

## 清理构建结果

使用 CMake 清理当前配置生成的目标文件：

```bash
cmake --build --preset debug --target clean
```

Flash 分区、链接地址和 MCU 平台迁移说明见根目录的 `firmware_arch.md`。
