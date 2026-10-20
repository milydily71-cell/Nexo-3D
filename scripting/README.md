# Nexo-3D C# scripting

This directory defines the planned C# gameplay scripting surface. Runtime hosting is not integrated yet.

## Example target API

```csharp
using Nexo3D;

public sealed class SpinBehaviour : Behaviour
{
    [Export] public float DegreesPerSecond { get; set; } = 45f;

    public override void Update(float deltaTime)
    {
        Transform.Rotate(Vector3.Up, DegreesPerSecond * deltaTime);
    }
}
```

The snippet is a design example, not currently compilable until the engine's `Behaviour`, `Export`, `Transform`, and `Vector3` APIs and managed runtime are implemented.

## Integration plan
1. Choose a supported .NET runtime/hosting model for desktop development and Android deployment.
2. Define stable C++/C# interop boundaries and object lifetime rules.
3. Add a managed script assembly loader and diagnostics.
4. Expose engine API types and a sample project.
5. Add script build checks and hot reload only after safety and lifecycle tests.
