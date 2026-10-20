using Nexo3D;

namespace Nexo3D.Samples;

public sealed class SpinBehaviour : Behaviour
{
    [Export(DisplayName = "Degrees per second", Category = "Motion")]
    public float DegreesPerSecond { get; set; } = 90f;

    public override void Update(float deltaTime)
    {
        Transform.Rotate(Vector3.Up, DegreesPerSecond * deltaTime);
    }
}
