<div align="center">

# CP-Code

*The **CP-Code** project, copyright [hellolin](https://hellolin.cf/) since 2023, under the [MPL-2.0](./LICENSE) license.*

</div>

## 简介

这个仓库存储 hellolin 自 `2023/08/19 00:00:00 (UTC+8)` 以来在各大 OJ 上解题的代码。

大多数代码都可在 [Virtual Judge](https://vjudge.net/) 找到，一些 VJudge 不支持的 OJ 可查看对应的账号。

## 文件结构

根目录下直接存放以 OJ 命名的文件夹，表示是在哪个 OJ 上解题的。区分大小写。

在此文件夹下，存放以比赛编号命名的文件夹，表示题目属于哪场比赛。若题目直属于题库则不设此文件夹。不区分大小写（优先小写）。

特别地，对于 Java 语言会有额外的文件夹归类。

在某道题目文件同级目录下可能含有编号相同的 `.md` 文件，该文件为我撰写的题解，可以在我的[个人博客](https://blog.hellolin.cf/)中找到。

## 使用指南

``` bash
git clone --depth=1 https://github.com/hellolin-oi/CP-Code # 克隆存储库
cd CP-Code # 进入存储库目录
git submodule update --init --recursive --depth=1 # 处理子模块
```

## 环境信息

时间和空间计量以此部分内容为准。

### 计算机

| 名称  | 信息   |
| ----: | :---- |
| CPU | `12th Gen Intel(R) Core(TM) i5-1240P (16) @ 1.700GHz` |
| RAM | 16GiB |

### 操作系统

**2023/08/29 之前**

| 名称  | 信息   |
| ----: | :---- |
| 系统版本 | `Windows 11 Pro for Workstations Insider Preview 22H2` |
| 内核版本 | `10.0.23531` |

**2023/08/29 之后**

| 名称  | 信息   |
| ----: | :---- |
| 系统版本 | `Ubuntu 22.04.3 LTS on Windows 10 x86_64` |
| 内核版本 | `4.4.0-23531-Microsoft` |

### 语言环境

以下，代码文件名默认为 `main.ext`，`ext` 是对应语言要求的拓展名。

**2023/08/29 之前**

| 名称 | 编译器/解释器版本 | 编译指令 | 运行指令 |
| ----: | :----------- | :------ | :------ |
| C | `gcc.exe (MinGW-W64 x86_64-ucrt-mcf-seh, built by Brecht Sanders) 13.2.0` | `gcc main.c -std=gnu2x -lm -O2 -DDEBUG -DLOCAL -o main` | `./main.exe` |
| C++(gcc) | `g++.exe (MinGW-W64 x86_64-ucrt-mcf-seh, built by Brecht Sanders) 13.2.0` | `g++ main.cpp -std=gnu++20 -lm -O2 -DDEBUG -DLOCAL -Wall -Wextra -mtune=native -march=native -fconstexpr-depth=2147483647 -Wl,--stack=2147483647 -o main` | `./main.exe` |
| C++(clang) | `(built by Brecht Sanders) clang version 16.0.6` | `clang++ main.cpp -std=gnu++20 -lm -O2 -DDEBUG -DLOCAL -Wall -Wextra -mtune=native -march=native -fconstexpr-depth=2147483647 -Wl,--stack=2147483647 -fuse-ld=lld -Wno-unknown-pragmas -o main` | `./main.exe` |

**2023/08/29 之后**

| 名称 | 编译器/解释器版本 | 编译指令 | 运行指令 |
| ----: | :----------- | :------ | :------ |
| C | `gcc-12 (Ubuntu 12.3.0-1ubuntu1~22.04) 12.3.0` | `gcc-12 main.c -std=gnu2x -lm -O2 -DLOCAL -o main` | `./main` |
| C++ | `Ubuntu clang version 15.0.7` | `clang++-15 main.cpp -std=gnu++20 -stdlib=libstdc++ -O2 -DLOCAL -Wall -Wextra -mtune=native -march=native -fconstexpr-depth=2147483647 -Wl,--stack=2147483647 -lm -fno-asm -ffast-math -fuse-ld=lld -Wno-unknown-pragmas -o main` | `./main` |
| Java | `openjdk 17.0.8 2023-07-18 LTS` | `javac main.java` | `java -DLOCAL=true main` |
| NodeJS | `v18.17.1` |  | `node main.js` |
| Python | `Python 3.10.12` | `python3 -m py_compile main.py` | `python3 main.py` |
| Lua | `Lua 5.4.4` | `luac main.lua -o main` | `lua main` |
