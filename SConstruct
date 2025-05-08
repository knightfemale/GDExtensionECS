#!/usr/bin/env python

env = SConscript("godot-cpp/SConstruct")

# 源文件配置
env.Append(CPPPATH=["src/", "thirdparty/entt/src/"])
sources = Glob("src/*.cpp")

# 添加调试模式判断逻辑
if env["target"] in ["editor", "template_debug"]: # Debug 模式配置
    # 如果想要在编辑器输出调试信息可以注释
    #env.Append(CPPDEFINES=["DEBUG_DISABLED"])
    # 禁用所有优化并添加调试符号
    if env["platform"] == "windows":
        env.Append(CFLAGS="/O2", CXXFLAGS="/O2")  # MSVC: /Od=禁用优化, /Zi=调试信息
    else:
        env.Append(CFLAGS="-O0", CXXFLAGS="-O0")    # GCC/Clang: -O0=无优化, -g=调试符号
    # 文档生成
    doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
    sources.append(doc_data)
else: # Release 模式配置
    # 关闭调试
    env.Append(CPPDEFINES=["DEBUG_DISABLED"])
    # 启用优化
    if env["platform"] == "windows":
        env.Append(CFLAGS="/Ox", CXXFLAGS="/Ox")  # MSVC 最大优化
    else:
        env.Append(CFLAGS="-O3", CXXFLAGS="-O3")  # GCC/Clang 最高优化

# 平台差异化配置（C++ 标准）
if env["platform"] == "windows":
    env.Append(CXXFLAGS="/std:c++17")
else:
    env.Append(CXXFLAGS="-std=c++17 -fPIC")  # 非 Windows 平台添加 -fPIC

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "demo/addons/GDExtensionECS/libgdextensionecs.{}.{}.framework/libgdexample.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
elif env["platform"] == "ios":
    if env["ios_simulator"]:
        library = env.StaticLibrary(
            "demo/addons/GDExtensionECS/libgdextensionecs.{}.{}.simulator.a".format(env["platform"], env["target"]),
            source=sources,
        )
    else:
        library = env.StaticLibrary(
            "demo/addons/GDExtensionECS/libgdextensionecs.{}.{}.a".format(env["platform"], env["target"]),
            source=sources,
        )
else:
    library = env.SharedLibrary(
        "demo/addons/GDExtensionECS/libgdextensionecs{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
