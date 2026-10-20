# Nexo-3D roadmap and feature register

This is the complete planning register for the native-first engine. A checked box means implemented and verified in source/tests; unchecked features are plans, not claims of existing functionality. UE5 is a quality/workflow reference, not a promise of feature parity.

## A. Native core
- [x] C++20 CMake project and native executable
- [x] Basic entity IDs, names, transforms and scene lookup
- [x] Native Android Java Activity / SurfaceView host source
- [x] JNI surface ownership and resize/touch event bridge
- [x] CPU-side geometry-grid line vertex generation
- [x] Sun, sky, cloud and graphics-preset configuration structures
- [ ] Native scene serialization and versioned project format
- [ ] Entity hierarchy, parent/child transforms and prefab instances
- [ ] Component registry and stable generational handles
- [ ] Event bus, job system and frame scheduler
- [ ] Structured logging, crash reporting and profiler overlays
- [ ] Asset/resource handles, async loading and lifetime tracking

## B. Vulkan renderer
- [x] Optional Vulkan loader/instance bootstrap
- [ ] Android VK_KHR_surface / VK_KHR_android_surface creation
- [ ] Physical-device selection and capability checks
- [ ] Swapchain lifecycle, resize and device-loss recovery
- [ ] Graphics queues, command pools, frame fences and frame pacing
- [ ] GPU vertex/index buffers and descriptor management
- [ ] SPIR-V shader build pipeline and shader hot reload
- [ ] Geometry-grid line-list draw path (uses CPU grid vertices)
- [ ] Camera matrices, depth buffer, frustum and culling
- [ ] PBR materials, metallic/roughness workflow and image-based lighting
- [ ] Directional sun light, cascaded shadow maps and soft shadows
- [ ] Atmosphere scattering model and sun disk
- [ ] Volumetric cloud raymarching with temporal reprojection
- [ ] HDR render targets and tone mapping
- [ ] Bloom, SSAO/GTAO, MSAA/TAA and color grading
- [ ] Mobile GPU bandwidth/thermal profiling and dynamic resolution

## C. Asset pipeline
- [ ] glTF 2.0 / GLB import, including meshes and node transforms
- [ ] Texture import, mip generation and GPU compression
- [ ] PBR material import and material instances
- [ ] Skeletal meshes, animation clips and skinning
- [ ] Collision mesh generation and LOD chains
- [ ] Asset browser, thumbnails, metadata and dependency graph
- [ ] Offline asset cooking and Android package bundling

## D. C# gameplay API
- [x] Vector math and transform operations
- [x] Entity IDs, scene/entity registry and component-script attachment
- [x] Export attributes for future inspector exposure
- [x] Debug logging and time/delta-time API
- [x] Behaviour lifecycle runner for managed preview/tests
- [ ] Native/managed scene synchronization and stable native handles
- [ ] Embedded .NET runtime strategy selected and licensed
- [ ] Android ARM64 runtime packaging and AOT/trimming validation
- [ ] C# <-> C++ marshalling and exception boundary
- [ ] Input API for touch, keyboard, gamepad and gestures
- [ ] Physics API and collision callbacks
- [ ] Coroutines/async tasks with engine-thread scheduling
- [ ] Script reload, exception panel and call-stack diagnostics
- [ ] Editor serialization of exported fields/properties
- [ ] API versioning and compatibility tests

## E. Physics and gameplay
- [ ] Fixed-step simulation and deterministic clock
- [ ] Rigid bodies, colliders, triggers and raycasts
- [ ] Character controller and mobile camera rig
- [ ] Animation state machines and root motion
- [ ] Audio source/listener, spatial audio and mixer
- [ ] Navigation mesh and AI steering
- [ ] Particle systems and GPU particle path
- [ ] UI runtime, localization and accessibility

## F. Native mobile editor
- [x] Android native SurfaceView host (foundation only)
- [ ] Native editor shell and dockable/panel navigation
- [ ] Real Vulkan viewport embedded in editor
- [ ] Scene hierarchy with selection and multi-select
- [ ] Transform gizmos, snapping and touch-friendly handles
- [ ] Inspector driven by component metadata and C# Export attributes
- [ ] Asset picker and GLB preview
- [ ] Undo/redo command history and autosave/recovery
- [ ] Multi-touch orbit, pan, pinch zoom and focus selection
- [ ] On-device project browser, import/export and package build
- [ ] Accessibility, tablet layout, keyboard/mouse support

## G. Production and tooling
- [x] C++ and C# CI workflow foundations
- [x] Android NDK cross-build workflow foundation
- [ ] Android APK/AAB packaging and install test
- [ ] Automated Vulkan validation-layer smoke tests on supported runners
- [ ] Performance budget tests on representative Android GPUs
- [ ] Device capability database and adaptive quality profiles
- [ ] Reproducible release artifacts, symbols and release notes
- [ ] Sample game, templates and offline documentation
- [ ] Plugin/module API and editor extension SDK

## Graphics preset intent
- **Mobile Low:** reduced render scale, 512 shadow map, no HDR/bloom/AO/cloud volume.
- **Mobile Balanced:** 1x scale, 1024 shadow map, HDR target; no expensive post effects by default.
- **Mobile High:** 2x MSAA where supported, 2048 shadow map, optional bloom and AO.
- **Cinematic:** high shadow resolution, volumetric clouds and post-processing when device budget permits.

Preset structures are currently configuration data. They do not become visual features until the renderer implements and validates the corresponding GPU passes.
