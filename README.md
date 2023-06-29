# TorrianiLang Compiler

### Prerequisites

Following Software need to be installed to build the programm:

- Clang or G++
- CMake
- Conan Package Manager
- LLVM Toolchain

**IMPORTANT**:
If you use the LLVM Toolchain you need to make shure that CMake support is enabled.
On Windows you specific need to install the Version with LLVM Support and not just download the .exe installer.

To do this, download the LLVM Source Code, and follow these steps:

Create build dir
```bash
mkdir build
cd build
```

Execute cmake
```bash
cmake ../llvm-project/llvm
```

Build and Install
```bash
cmake --build .
cmake --build . --target install
```