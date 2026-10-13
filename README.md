# C++控制台单词本 (Word Bank)

一个基于 C++ 的控制台英语单词记忆与测验程序。

## 功能
- 单词的增删改查
- 中文释义测试（积分制、生命值、提示功能）
- 数据持久化（使用 `dict.txt` 追加存储）

## 技术栈
- C++ (STL, 文件流, 控制台彩色输出)
- CMake (构建系统)
- VS Code (IDE)

## 编译方法
```bash
mkdir build
cd build
cmake ..
cmake --build .
