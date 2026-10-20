# Nexo-3D

**A mobile-first 3D game engine and editor** — an ambitious open-source project inspired by Unreal Engine workflows, built incrementally around C++, Vulkan, and C# scripting.

> Status: early scaffold. This repository is not yet a production-ready UE5 replacement. Features below are target roadmap items, not claims of completed functionality.

## Vision
- **C++ runtime:** modular engine core, scene graph, entity/component system, resource and asset management.
- **Rendering:** Vulkan-first renderer with mobile-friendly fallback strategy, PBR materials, shadows, HDR/tonemapping, post-processing, and scalable quality presets.
- **Mobile editor:** touch-friendly scene hierarchy, inspector, asset browser, viewport controls, and script editor; start as a responsive web prototype, then connect native tooling.
- **C# scripting:** managed gameplay scripts, engine API bindings, and examples.
- **GLB/glTF assets:** import 3D models and animations.
- **GitHub workflows:** automated checks and builds, with artifacts published only after CI succeeds.

## Planned feature groups (50+ target)
1. **Core:** application lifecycle, logging, settings, event bus, job system, memory utilities, profiling.
2. **World:** scenes, entities, components, transforms, hierarchy, prefabs, serialization, undo/redo.
3. **Rendering:** Vulkan device, swapchain, render graph, meshes, PBR, materials, textures, lighting, shadows, sky, fog, particles, instancing, culling, LOD, MSAA, HDR, tone mapping, bloom, SSAO, anti-aliasing, debug views, render scaling, quality presets.
4. **Assets:** glTF/GLB, textures, animation clips, skeletons, import settings, asset database, thumbnails, hot reload.
5. **Gameplay:** cameras, input mapping, physics integration, collision, audio, animation state machines, navigation, UI, localization, save/load, networking hooks.
6. **Editor:** mobile-first layout, viewport, hierarchy, inspector, asset browser, script editor, console, gizmos, play/stop, project settings, templates, build/export panel, touch gestures, keyboard shortcuts, autosave, undo/redo.
7. **C# tooling:** script API, compiler/runtime integration, diagnostics, examples, reload pipeline.
8. **Build/release:** CMake, tests, Android NDK build, GitHub Actions, artifact packaging, versioned releases, crash diagnostics hooks.

## Repository layout
```text
Nexo-3D/
├── .github/workflows/ci.yml
├── editor/                 # Responsive mobile editor prototype
├── engine/                 # C++ runtime and renderer
├── scripting/              # C# gameplay API examples and design
├── tests/
├── CMakeLists.txt
└── README.md
```

## Build the C++ starter
Requires CMake 3.20+ and a C++20 compiler.

```bash
cmake -S . -B build
cmake --build build --config Release
./build/nexo3d
```

The initial CI target is intentionally dependency-light. Vulkan/Android SDK integration will be added in dedicated, testable steps.

## Roadmap
- [x] Repository scaffold and CI baseline
- [x] Mobile editor UI prototype
- [x] C++20 engine-core entry point
- [ ] Scene graph and entity/component model
- [ ] Vulkan renderer and Android surface
- [ ] GLB importer and asset pipeline
- [ ] C# runtime integration and sample scripts
- [ ] Android editor packaging and playable sample project

## Design principles
Mobile-first, modular, measurable performance, explicit feature status, open formats, reproducible builds, and no secrets committed to the repository.
