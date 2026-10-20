namespace Nexo3D;

[AttributeUsage(AttributeTargets.Property | AttributeTargets.Field)]
public sealed class ExportAttribute : Attribute
{
}

public readonly record struct Vector3(float X, float Y, float Z)
{
    public static Vector3 Zero => new(0, 0, 0);
    public static Vector3 Up => new(0, 1, 0);
    public static Vector3 One => new(1, 1, 1);
}

public sealed class Transform
{
    public Vector3 Position { get; set; } = Vector3.Zero;
    public Vector3 RotationDegrees { get; set; } = Vector3.Zero;
    public Vector3 Scale { get; set; } = Vector3.One;

    // The native engine binding will implement this operation in a later milestone.
    public void Rotate(Vector3 axis, float degrees)
    {
        _ = axis;
        _ = degrees;
        throw new NotSupportedException("Transform.Rotate requires the native runtime bridge.");
    }
}

public abstract class Behaviour
{
    public Transform Transform { get; } = new();
    public virtual void OnCreate() { }
    public virtual void Update(float deltaTime) { }
    public virtual void OnDestroy() { }
}
