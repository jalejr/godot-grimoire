#!/usr/bin/env python
import os
import sys

from methods import print_error


libname = "grimoire"
projectdir = "project"

localEnv = Environment(tools=["default"], PLATFORM="")

# Build profiles can be used to decrease compile times.
# You can either specify "disabled_classes", OR
# explicitly specify "enabled_classes" which disables all other classes.
# Modify the example file as needed and uncomment the line below or
# manually specify the build_profile parameter when running SCons.

# localEnv["build_profile"] = "build_profile.json"

customs = ["custom.py"]
customs = [os.path.abspath(path) for path in customs]

opts = Variables(customs, ARGUMENTS)
opts.Update(localEnv)

Help(opts.GenerateHelpText(localEnv))

env = localEnv.Clone()

if not (os.path.isdir("godot-cpp") and os.listdir("godot-cpp")):
    print_error("""godot-cpp is not available within this folder, as Git submodules haven't been initialized.
Run the following command to download godot-cpp:

    git submodule update --init --recursive""")
    sys.exit(1)

env = SConscript("godot-cpp/SConstruct", {"env": env, "customs": customs})

env.Append(CPPPATH=["include/"])
env.Append(CPPPATH=["src/"])
env.Append(CPPPATH=["tag-system-src/include"])
env.Append(CPPPATH=["tag-system-src/src"])
env.Append(CPPPATH=["attribute-system-src/include"])
env.Append(CPPPATH=["attribute-system-src/src"])
env.Append(CPPPATH=["event-system-src/include"])
env.Append(CPPPATH=["event-system-src/src"])
env.Append(CPPPATH=["effect-system-src/include"])
env.Append(CPPPATH=["effect-system-src/src"])
env.Append(CPPPATH=["ability-system-src/include"])
env.Append(CPPPATH=["ability-system-src/src"])

sources = Glob("tag-system-src/src/*.cpp")
sources += Glob("attribute-system-src/src/*.cpp")
sources += Glob("event-system-src/src/*.cpp")
sources += Glob("effect-system-src/src/*.cpp")
sources += Glob("ability-system-src/src/*.cpp")
sources += Glob("src/*.cpp")

if env["target"] in ["editor", "template_debug"]:
    try:
        doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
        sources.append(doc_data)
    except AttributeError:
        print("Not including class reference as we're targeting a pre-4.3 baseline.")

# .dev doesn't inhibit compatibility, so we don't need to key it.
# .universal just means "compatible with all relevant arches" so we don't need to key it.
suffix = env['suffix'].replace(".dev", "").replace(".universal", "")

lib_filename = "{}{}{}{}".format(env.subst('$SHLIBPREFIX'), libname, suffix, env.subst('$SHLIBSUFFIX'))

library = env.SharedLibrary(
    "bin/{}/{}".format(env['platform'], lib_filename),
    source=sources,
)

copy = env.Install("{}/addons/grimoire/bin/{}/".format(projectdir, env["platform"]), library)

default_args = [library, copy]
Default(*default_args)
