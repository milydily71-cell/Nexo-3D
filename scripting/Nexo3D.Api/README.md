# Nexo3D.Api

Managed gameplay-facing API for Nexo-3D. This first functional layer provides vector math, transforms, entity/scene management, exported inspector metadata, logging, time, and a managed script lifecycle runner.

## Important runtime boundary

This is a usable managed API and preview/test runtime, **not yet a production native C# host**. The C++ engine does not currently load these assemblies or synchronize this managed scene with the native scene. A later milestone must select/package a supported .NET embedding/runtime strategy, implement stable native handles and marshalling, and test Android ABI compatibility before scripts can run inside the native Android game.

## Example

```csharp
using Nexo3D;

var scene = new Scene();
var cube = scene.CreateEntity("Cube");
var spin = cube.AddBehaviour<SpinBehaviour>();
var runtime = new ScriptRuntime(scene);
runtime.Tick(1f / 60f);
```

Behaviour lifecycle order: first tick calls `OnCreate`; active scripts receive `OnEnable` once and then `Update`; inactive/disabled scripts receive `OnDisable` when leaving the enabled state. `OnDestroy` runs when a behaviour or entity is removed.
