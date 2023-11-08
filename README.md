# CP-Code

## 简介

这个仓库存储 hellolin 在各个 OJ 上解题的代码。理论上你能从这里找到大部分我的代码，可参考下方的 OJ 列表查找提交记录。

## OJ 列表

| 简写（文件夹名称） | 全称 | 个人账号 | 开放注册 | 主要语言 | 附加说明 |
| ---------------- | --- | ------- | ------ | ------- | ------- |
| AtCoder | [AtCoder](https://atcoder.jp/) | [hellolin](https://atcoder.jp/users/hellolin) | 是 | 日语、英语 |  |
| BaekjoonOJ | [Baekjoon Online Judge](https://www.acmicpc.net/) | [hellolin](https://www.acmicpc.net/user/hellolin) | 是 | 韩语、英语 |  |
| CodeChef | [CodeChef](https://www.codechef.com/) | [hellolin](https://www.codechef.com/users/hellolin) | 是 | 英语、俄语、简体中文 |  |
| CodeForces | [CodeForces](https://codeforces.com/) | [hellolin](https://codeforces.com/profile/hellolin) | 是 | 俄语、英语 |  |
| DarkBZOJ | [黑暗爆炸 OJ](https://darkbzoj.cc/) | [hellolin](https://darkbzoj.cc/user/profile/hellolin) | 是 | 简体中文 |  |
| Eolymp | [Eolymp](https://www.eolymp.com/) | [hellolin](https://www.eolymp.com/users/hellolin) | 是 | 英语 |  |
| Gym | [CodeFoces::Gym](https://codeforces.com/gyms) | [hellolin](https://codeforces.com/profile/hellolin) | 是 | 俄语、英语 |  |
| HDU | [Hangzhou Dianzi University Online Judge](https://acm.hdu.edu.cn/) | [hellolin](https://acm.hdu.edu.cn/userstatus.php?user=hellolin) | 是 | 英语、简体中文 |  |
| LeetCode | [力扣](https://leetcode.cn/) | [imhellolin](https://leetcode.cn/u/imhellolin) | 是 | 简体中文、英语 |  |
| LibreOJ | [LibreOJ](https://loj.ac/) | [hellolin](https://loj.ac/u/hellolin) | 是 | 简体中文、英语、日语 |  |
| Luogu | [洛谷](https://www.luogu.com.cn/) | [hellolin](https://www.luogu.com.cn/users/751017) | 是 | 简体中文 | 仅记录 P 题库和 B 题库。 |
| NFLSOJ | [NFLSOJ](http://www.nfls.com.cn:10611/) | [hellolin_oi](http://www.nfls.com.cn:10611/user/1186) | 否 | 简体中文 |  |
| POJ | [PKU JudgeOnline](http://poj.org/) | [hellolin](http://poj.org/userstatus?user_id=hellolin) | 是 | 英语、简体中文 |  |
| QOJ | [QOJ](https://qoj.ac/) | [hellolin](https://qoj.ac/user/profile/hellolin) | 是 | 简体中文、繁体中文、英语 |  |
| SPOJ | [Sphere Online Judge](https://www.spoj.com/) | [hellolin](https://www.spoj.com/users/hellolin) | 是 | 英语 |  |
| TopCoder | [TopCoder](https://www.topcoder.com/) | [hellolin](https://profiles.topcoder.com/hellolin) | 是 | 英语 |  |
| UniversalOJ | [Universal Online Judge](https://uoj.ac) | [hellolin](https://uoj.ac/user/profile/hellolin) | 是 | 简体中文、英语 |  |
| UVaOJ | [UVa Online Judge](https://onlinejudge.org/) | hellolin | 是 | 英语 |  |


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

| 名称  | 信息   |
| ----: | :---- |
| 系统版本 | `Ubuntu 22.04.3 LTS on Windows 10 x86_64` |
| 内核版本 | `5.15.90.4-microsoft-standard-WSL2` |

### 语言环境

以下，代码文件名默认为 `main.ext`，`ext` 是对应语言要求的拓展名。

| 名称 | 编译器/解释器版本 | 编译指令 | 运行指令 |
| ----: | :----------- | :------ | :------ |
| C | `gcc-12 (Ubuntu 12.3.0-1ubuntu1~22.04) 12.3.0` | `gcc-12 main.c -std=gnu2x -lm -O2 -DLOCAL -o main` | `./main` |
| C++ | `Ubuntu clang version 15.0.7` | `clang++-15 main.cpp -std=gnu++20 -stdlib=libstdc++ -O2 -DLOCAL -Wall -Wextra -mtune=native -march=native -fconstexpr-depth=2147483647 -Wl,--stack=2147483647 -lm -fno-asm -ffast-math -fuse-ld=lld -o main` | `./main` |
| Java | `openjdk 17.0.8 2023-07-18 LTS` | `javac main.java` | `java -DLOCAL=true main` |
| NodeJS | `v18.17.1` |  | `node main.js` |
| Python | `Python 3.10.12` |  | `python3 main.py` |
