# GDExtensionECS

#### Introduction 介绍

A simple ECS framework with minimally invasive on Godot native nodes. Due to my limited technical capabilities, this framework can only achieve compositional development, and its performance improvement is very limited (in fact, even in cases where components are not complex, it may lead to performance degradation). Therefore, it only serves as a starting point for further discussions.

一个简单的对 Godot 原生节点最小侵入性的 ECS 框架，由于本人的技术能力有限，因此次框架仅能实现组合式开发，对性能提升十分有限（甚至在组件不复杂的情况下，是负提升），因此仅做抛砖引玉的作用。

This might also be able to GDScript replace code with C# code to improve System operational efficiency of the node.

这个可能也能将 GDScript 代码换成 C# 代码运行以提高 System 节点的运行效率。

In the future, integration of the Entt framework may be achieved.

在未来，可能实现集成 Entt 框架。

#### Installation Tutorial 安装教程

##### Clone Source Code 拉取源码

```git bash
git clone --recurse-submodules https://github.com/knightfemale/GDExtensionECS.git
```

##### Compile the Project 编译项目

```cmd
# Prepare the compilation environment 准备编译环境
conda create -n your_env_name python=3.11
conda activate your_env_name
pip install scons

# Compile the project 编译项目
cd path_to_your_project
scons platform=windows target=editor
scons platform=windows target=template_release
scons platform=windows target=template_debug
```

#### Usage Instructions 使用说明

After compilation is complete, or directly download the Releases file. The  demo  folder is the implementation of GDExtension, and the  gds - demo  folder is the implementation of GDScript. It can be directly opened using Godot 4.4.1.

编译完成或者直接下载 Releases 文件，使用 Godot4.4.1 直接打开`demo`文件夹。

#### Thank - you List 感谢名单

玩物不丧志的老李
https://github.com/LiGameAcademy
