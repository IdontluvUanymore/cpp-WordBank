# C++控制台单词本 (Word Bank)

一个基于 C++ 的控制台英语单词记忆与测验程序。
在背六级单词时，想到可以试着通过写个类似百词斩的控制台程序来捡起以前学的C++知识，顺便帮我背单词。

## 功能
- 单词的增删改查
- 中文释义测试（积分制、生命值、提示功能）
- 数据持久化（使用 `dict.txt` 追加存储）

## 技术栈
- C++ (STL, 文件流...)
- CMake (构建系统)
- Visual Studio(MSVC) (编译器)

## 编译方法
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## 踩坑记录
- 解决了Windows控制台中文乱码问题 (SetConsoleCP/SetConsoleOutputCP)
- 解决了Windows下UTF-8 with BOM导致的C2001编译报错
