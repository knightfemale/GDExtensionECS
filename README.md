# GDExtensionECS

#### Introduction 介绍

A minimal-intrusion ECS framework for Godot's native nodes. Due to my limited technical capabilities, this framework currently only supports compositional development and offers very limited performance improvements (in fact, it may even cause performance degradation for simple components). Thus, it primarily serves as a starting point for discussion rather than a complete solution.

一个简单的对 Godot 原生节点最小侵入性的 ECS 框架，由于本人的技术能力有限，因此次框架仅能实现组合式开发，对性能提升十分有限（甚至在组件不复杂的情况下，是负提升），因此仅做抛砖引玉的作用。

I initially attempted to integrate existing ECS frameworks like entt and entityx, but they distinguish components by type. However, in Godot's editor, subclasses inherited from the base Component class do not register as new types in GDExtension. To address this, I rewrote the entire framework from scratch using sparse sets, specifically tailored for GDExtension compatibility.

中间尝试过集成 entt、entityx 等框架，但他们都是根据类型区分不同组件，而在 Godot 编辑器集继承自 Component 基类似乎在 GDExtension 里并不会成为新的类型，因此我从底层重写了一套基于稀疏集的适用于 GDExtension 的这个 ECS 框架。

It seems these component nodes cannot be directly used in Godot C# code?

在 Godot C# 代码里似乎无法直接使用这些节点？

Automatic multithreading will be implemented in the near future.

自动多线程将会在不久的将来实现。

This plugin will continue to be updated alongside Godot versions, but previous versions may not be maintained. Theoretically, you can build your own version to ensure compatibility.

该插件会随着 Godot 版本更新而继续更新，但可能不会维护之前的版本。理论上，你可以自己构建实现兼容。

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
scons platform=windows target=template_release
scons platform=windows target=template_debug
```

#### Usage Instructions 使用说明

After compilation is complete, or directly download the Releases file. The  demo  folder is the implementation of GDExtension, and the  gds - demo  folder is the implementation of GDScript. It can be directly opened using Godot 4.4.1.

编译完成或者直接下载 Releases 文件，使用 Godot4.4.1 直接打开`demo`文件夹。

#### Thank - you List 感谢名单

玩物不丧志的老李
https://github.com/LiGameAcademy
