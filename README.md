# C++ Playground

单文件 C++ 练习模板。**一个文件夹里随便丢 `.cpp`，每个文件独立 `main`，F5 直接编译+调试当前文件。**

支持 **macOS / Windows(MinGW) / Linux**，零构建系统依赖。

## 工具链（只需两个扩展）

| 扩展 | 用途 |
|------|------|
| `llvm-vs-code-extensions.vscode-clangd` | 补全 / 诊断 / 跳转 |
| `vadimcn.vscode-lldb` | 调试（三平台统一用 lldb） |

> `ms-vscode.cpptools` **不需要**，可以卸载。

## 快速开始

```bash
git clone <repo> cpp-playground
cd cpp-playground
code .
```

首次打开，把对应平台的 settings 复制成 `.vscode/settings.json`：

- **macOS / Linux**：复制 `.vscode/settings.macos.json`
- **Windows MinGW**：复制 `.vscode/settings.windows.json`

```bash
# macOS / Linux
cp .vscode/settings.macos.json .vscode/settings.json

# Windows (PowerShell)
Copy-Item .vscode/settings.windows.json .vscode/settings.json
```

然后：打开任意 `.cpp` → 设断点 → **F5**。

## 工作原理

- `tasks.json`：用 `${file}` 只编译**当前打开的文件**，产物输出到 `output/`
- `launch.json`：一个 `lldb` 配置三平台通用，`preLaunchTask` 自动先编译
- `.clangd` + `compile_flags.txt`：让 clangd 以 C++20 分析每个单文件
- `settings.json` 通过 `${config:cppSingleFile.compiler}` 读本机编译器路径

## 目录结构

```
cpp-playground/
├── .vscode/
│   ├── tasks.json                # 编译当前文件
│   ├── launch.json               # 调试（lldb，三平台通用）
│   ├── settings.macos.json       # macOS/Linux 配置模板
│   └── settings.windows.json     # Windows MinGW 配置模板
├── .clangd                       # clangd 项目配置
├── compile_flags.txt             # 单文件模式编译参数
├── .gitignore
├── hello.cpp
├── optional.cpp
└── variant.cpp
```

## 新增一个练习

直接新建 `xxx.cpp`（要有 `main`），打开后按 F5 即可。产物自动进 `output/`，不污染源码目录。

## 常见问题

**Q: Windows 上输出文件有 `.exe` 后缀吗？**
A: 有。MinGW 的 g++ 在 Windows 上会自动给无后缀的 `-o` 目标补 `.exe`。launch.json 里 `program` 不写后缀也能匹配，CodeLLDB 会正确处理。

**Q: clangd 报 `No template named 'optional'`？**
A: 说明 clangd 没进 C++20 模式。检查 `.clangd` 是否存在、`compile_flags.txt` 是否有 `-std=c++20`，然后 `Cmd/Ctrl+Shift+P` → `clangd: Restart language server`。

**Q: 能升级到 CMake 多文件项目吗？**
A: 能。加一个生成 `compile_commands.json` 的 `CMakeLists.txt`，clangd 自动切换到多文件模式，tasks/launch 基本不用改。
