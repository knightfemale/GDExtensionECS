# GDExtensionECS

#### 介绍

一个简单的对 Godot 原生节点最小侵入性的 ECS 框架，由于本人的技术能力有限，因此次框架仅能实现组合式开发，对性能提升十分有限（甚至在组件不复杂的情况下，是负提升），因此仅做抛砖引玉的作用。

这个可能也能将 GDScript 代码换成 C# 代码运行以提高 System 节点的运行效率。

在未来，可能实现集成 Entt 框架。

#### 安装教程

##### 拉取源码

```git bash
git clone --recurse-submodules https://github.com/knightfemale/GDExtensionECS.git
```

##### 编译项目

```
# 准备编译环境
conda create -n your_env_name python=3.11
conda activate your_env_name
pip install scons
# 编译项目
cd path_to_your_project
scons platform=windows target=editor
scons platform=windows target=template_release
scons platform=windows target=template_debug
```

#### 使用说明

编译完成或者直接下载 Releases 文件，`demo`文件夹为 GDExtension 的实现，`gds-demo`文件夹为 GDScript 的实现。
使用 Godot4.4.1 直接打开

#### 感谢名单

玩物不丧志的老李
https://github.com/LiGameAcademy
