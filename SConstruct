import os

godot_project_dir = os.getcwd()
godot_sconstruct_path = os.path.join(godot_project_dir, "godot-cpp", "SConstruct")
extension_name = "example"
lib_name = "example"
source_dir = os.path.join(godot_project_dir, "src")
build_dir = os.path.join(godot_project_dir, "build")
bin_dir = os.path.join(godot_project_dir, "project", "addons", extension_name, "bin")
vcpkg_installed_dir = os.path.join(godot_project_dir, "vcpkg_installed")

env = SConscript(godot_sconstruct_path)

# Detect the platform
platform = env["platform"]
print("platform: ", platform)

# Set up the source files
sources = Glob("src/*.cpp")

# Platform-specific configurations
if platform == "windows":
    vcpkg_triplet = "x64-windows"
    env.Append(CXXFLAGS=["/std:c++17", "/Zc:__cplusplus", "/permissive-"])
elif platform == "linux":
    vcpkg_triplet = "x64-linux"
    env.Append(CXXFLAGS=["-std=c++17", "-fexceptions"])
elif platform == "macos":
    vcpkg_triplet = "arm64-osx" if env["arch"] == "arm64" else "x64-osx"
    env.Append(CXXFLAGS=["-std=c++17", "-fexceptions"])
elif platform == "ios":
    vcpkg_triplet = "arm64-ios"
    env.Append(CXXFLAGS=["-std=c++17", "-fexceptions"])
elif platform == "android":
    vcpkg_triplet = "arm64-android"
    env.Append(CXXFLAGS=["-std=c++17", "-fexceptions"])
elif platform == "web":
    vcpkg_triplet = "wasm32-emscripten"
    env.Append(CXXFLAGS=["-std=c++17", "-s", "USE_PTHREADS=1"])
    env.Append(LINKFLAGS=["-s", "USE_PTHREADS=1"])

# VTK and ITK configurations
env.Append(
    CPPPATH=[
        f"{vcpkg_installed_dir}/{vcpkg_triplet}/include",
        f"{vcpkg_installed_dir}/{vcpkg_triplet}/include/ITK-5.4",
    ]
)
env.Append(LIBPATH=[f"{vcpkg_installed_dir}/{vcpkg_triplet}/lib"])
vcpkg_libs = ["ITKCommon-5.4"]
env.Append(LIBS=vcpkg_libs)  # Add more specific libraries as needed

# Build the shared library
if platform == "macos":
    lib_dir = f"{bin_dir}/lib{lib_name}.{env['platform']}.{env['target']}.framework/{lib_name}.{env['platform']}.{env['target']}"
elif platform == "web":
    lib_dir = f"{bin_dir}/lib{lib_name}.wasm"
else:
    lib_dir = f"{bin_dir}/lib{lib_name}.{env['platform']}.{env['target']}.{env['arch']}{env['SHLIBSUFFIX']}"

library = env.SharedLibrary(lib_dir, source=sources)

Default(library)
