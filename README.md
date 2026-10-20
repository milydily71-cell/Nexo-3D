# Nexo-3D

**Nexo-3D is a native-first, mobile-first 3D engine/editor project.** The target stack is C++20 + Vulkan for engine/rendering, Java for Android lifecycle and touch/surface hosting, and a custom C# API for gameplay scripts. The editor is not HTML/WebView based.

> **Status:** early engine foundation. This is not yet a working 3D editor or a UE5 replacement. The roadmap distinguishes code foundations from features that still need GPU/runtime implementation.

## Implemented source foundations
- C++20 CMake engine and basic scene/entity/transform model.
- Optional Vulkan loader and instance bootstrap (not a swapchain or draw pipeline).
- CPU geometry-grid line vertex generation; environment configuration for directional sun, sky/cloud parameters, and four graphics quality presets.
- Java SurfaceView Activity, Android manifest, and JNI surface lifecycle/touch bridge source.
- C# gameplay API foundation: vector math, transforms, scene/entity registry, exported property metadata, logging, time, and managed behaviour lifecycle runner.
- C++/C# CI foundations and Android NDK native build workflow.

## Native Android architecture
- Android Java Activity: Android host, native surface and touch events.
- engine/src/android_jni.cpp: JNI bridge and ANativeWindow lifecycle.
- engine/include/nexo/environment.hpp: grid vertex data and sky/sun/cloud settings.
- engine/include/nexo/render_presets.hpp: Mobile Low, Balanced, High and Cinematic quality profiles.
- engine/src/vulkan_renderer.cpp: Vulkan instance bootstrap only.

The Android host currently establishes the platform integration boundary. It does **not** yet create a Vulkan Android surface/swapchain or submit frames, so no claim is made that the grid, sun, or clouds are already visible on-device. The renderer must implement those GPU passes next. The render design is geometry-driven: do not replace the viewport with a flat clear-color background.

## Build locally

C++20 compiler and CMake 3.20+:

```bash
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build --output-on-failure
./build/nexo3d
```

C# (.NET 8 SDK):

```bash
dotnet build scripting/Nexo3D.Api/Nexo3D.Api.csproj --configuration Release
dotnet build scripting/Samples/Samples.csproj --configuration Release
```

Android NDK cross-build (requires Android NDK):

```bash
cmake -S . -B build-android \
  -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake" \
  -DANDROID_ABI=arm64-v8a \
  -DANDROID_PLATFORM=android-26 \
  -DNEXO_ENABLE_VULKAN=ON
cmake --build build-android --parallel 2
```

This is a native library cross-build, not yet a complete Gradle APK packaging workflow.

## Complete planned feature register
See docs/ROADMAP.md for the full checklist across native core, Vulkan, assets, C# runtime, physics/gameplay, mobile editor, and production tooling.

Graphics presets are configuration intent only until the corresponding GPU passes are implemented. Volumetric clouds, PBR, shadows, HDR, bloom, AO and temporal anti-aliasing are planned work—not finished claims.

## License and scope
Nexo-3D is an independent project. UE5-inspired graphics presets describe target quality tiers, not Epic Engine code or feature parity.
