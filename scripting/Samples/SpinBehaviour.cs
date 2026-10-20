using Nexo3D;

public sealed class SpinBehaviour : Behaviour
{
    [Export]
    public float DegreesPerSecond { get; set; } = 45f;

    public override void Update(float deltaTime)
    {
        // Example API usage. Native Transform.Rotate is not wired up yet.
        var step = DegreesPerSecond * deltaTime;
        Transform.RotationDegrees = new Vector3(
            Transform.RotationDegrees.X,
            Transform.RotationDegrees.Y + step,
            Transform.RotationDegrees.Z);
    }
}
