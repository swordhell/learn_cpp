# 概述

测试一下 c++20 modules

## 使用编译环境

```bash
clang++ --version
Apple clang version 16.0.0 (clang-1600.0.26.4)
Target: arm64-apple-darwin24.1.0
Thread model: posix
```

这个版本是不能支持 c++ 20

需要使用brew来安装新版本的。


2. 添加 Ubuntu Toolchain PPA

Ubuntu 默认软件仓库中的 GCC 可能较旧。可以通过添加 Toolchain PPA 获取最新版本：

```bash
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt update
sudo apt install gcc-13 g++-13

sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 100
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 100
```
