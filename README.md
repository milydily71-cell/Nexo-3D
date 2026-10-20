# Nexo-3D

**A mobile-first 3D game engine and editor** inspired by Unreal Engine workflows, built incrementally around C++, Vulkan, and C# gameplay scripting.

> Status: early development scaffold. This is not a production-ready UE5 replacement. Features listed as roadmap items are not yet implemented.

## Current foundation
- C++20 native engine executable.
- Scene model with entity IDs, names, transforms, lookup, and basic tests.
- Optional Vulkan loader integration and Vulkan instance bootstrap when the SDK/loader is available.
- Initial C# gameplay API project (Nexo3D.Api) and a compiling sample script project.
- Responsive mobile editor prototype at editor/index.html.
- GitHub Actions CI for C++ build/tests and C# compilation, plus an Android NDK cross-compile workflow.

## Build locally

C++20 compiler and CMake 3.20+:

```bash
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build --output-on-failure
./build/nexo3d
```

Vulkan integration is optional. If Vulkan development files are installed, CMake enables the Vulkan instance bootstrap. Without them, the engine still builds, but the renderer is unavailable.

C# API and sample (requires .NET 8 SDK):

```bash
dotnet build scripting/Nexo3D.Api/Nexo3D.Api.csproj
dotnet build scripting/Samples/Samples.csproj
```

Android NDK cross-build (requires Android NDK):

```bash
cmake -S . -B build-android \\
  -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake" \\
  -DANDROID_ABI=arm64-v8a \\
  -DANDROID_PLATFORM=android-26 \\
  -DNEXO_ENABLE_VULKAN=OFF
cmake --build build-android --parallel 2
```

## Repository map

- .github/workflows/ci.yml: C++ tests and C# build checks.
- .github/workflows/android-build.yml: Android arm64 native cross-build.
- engine/include/nexo/scene.hpp: initial scene/entity/transform model.
- engine/include/nexo/vulkan_renderer.hpp and engine/src/vulkan_renderer.cpp: Vulkan bootstrap interface and implementation.
- editor/index.html: touch-friendly editor UI prototype (viewport is not a real 3D renderer yet).
- scripting/Nexo3D.Api: initial C# API types.
- scripting/Samples: example gameplay script.

## Roadmap

1. **Native foundation:** scene graph, resource handles, input/events, logging, profiling.
2. **Android Vulkan renderer:** Android surface and swapchain, physical-device selection, command buffers, shaders, mesh draw path.
3. **Assets:** GLB/glTF import, textures, materials, animation.
4. **C# runtime:** choose and integrate a supported managed runtime, native interop, script lifecycle, diagnostics.
5. **Editor:** connect hierarchy/inspector to a real scene model, then render an interactive 3D viewport.
6. **Graphics:** PBR, shadow maps, HDR, tone mapping, bloom, SSAO, anti-aliasing, LOD and scalable mobile presets.
7. **Production:** Android packaging, project export, reproducible CI artifacts, crash diagnostics.

## Target design

- Android phones and tablets first.
- C++20 runtime; Vulkan as the intended native rendering backend.
- C# gameplay scripting with a custom Nexo API.
- 50+ planned engine features delivered in tested increments.
- Explicit feature status, open formats, reproducible builds, and no secrets committed to source control.
