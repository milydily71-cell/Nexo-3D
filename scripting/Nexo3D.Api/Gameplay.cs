using NumericsMatrix4x4 = System.Numerics.Matrix4x4;
using NumericsVector3 = System.Numerics.Vector3;

namespace Nexo3D;

[AttributeUsage(AttributeTargets.Property | AttributeTargets.Field)]
public sealed class ExportAttribute : Attribute
{
    public string? DisplayName { get; init; }
    public string? Category { get; init; }
}

public readonly record struct EntityId(ulong Value)
{
    public bool IsValid => Value != 0;
    public override string ToString() => Value.ToString();
}

public readonly record struct Vector3(float X, float Y, float Z)
{
    public static Vector3 Zero => new(0, 0, 0);
    public static Vector3 One => new(1, 1, 1);
    public static Vector3 Up => new(0, 1, 0);
    public static Vector3 Right => new(1, 0, 0);
    public static Vector3 Forward => new(0, 0, -1);
    public float Length => MathF.Sqrt(X * X + Y * Y + Z * Z);
    public Vector3 Normalized => Length > 1e-6f ? this / Length : Zero;
    public static Vector3 operator +(Vector3 a, Vector3 b) => new(a.X+b.X,a.Y+b.Y,a.Z+b.Z);
    public static Vector3 operator -(Vector3 a, Vector3 b) => new(a.X-b.X,a.Y-b.Y,a.Z-b.Z);
    public static Vector3 operator *(Vector3 a, float s) => new(a.X*s,a.Y*s,a.Z*s);
    public static Vector3 operator *(float s, Vector3 a) => a*s;
    public static Vector3 operator /(Vector3 a, float s) => Math.Abs(s) < 1e-8f ? Zero : new(a.X/s,a.Y/s,a.Z/s);
    public static float Dot(Vector3 a, Vector3 b) => a.X*b.X+a.Y*b.Y+a.Z*b.Z;
    public static Vector3 Cross(Vector3 a, Vector3 b) => new(a.Y*b.Z-a.Z*b.Y,a.Z*b.X-a.X*b.Z,a.X*b.Y-a.Y*b.X);
    internal NumericsVector3 ToNumerics() => new(X,Y,Z);
}

public sealed class Transform
{
    public Vector3 Position { get; set; } = Vector3.Zero;
    public Vector3 RotationDegrees { get; set; } = Vector3.Zero;
    public Vector3 Scale { get; set; } = Vector3.One;
    public void Translate(Vector3 delta) => Position += delta;
    public void Rotate(Vector3 axis, float degrees)
    {
        var n = axis.Normalized;
        if (n == Vector3.Zero || !float.IsFinite(degrees)) return;
        RotationDegrees += n * degrees;
    }
    public void LookAt(Vector3 target)
    {
        var d = target - Position;
        if (d.Length < 1e-6f) return;
        var yaw = MathF.Atan2(d.X, -d.Z);
        var pitch = MathF.Atan2(d.Y, MathF.Sqrt(d.X*d.X+d.Z*d.Z));
        RotationDegrees = new(pitch * 180f / MathF.PI, yaw * 180f / MathF.PI, 0);
    }
    public NumericsMatrix4x4 ToMatrix()
    {
        var radians = MathF.PI / 180f;
        return NumericsMatrix4x4.CreateScale(Scale.ToNumerics())
            * NumericsMatrix4x4.CreateFromYawPitchRoll(RotationDegrees.Y*radians, RotationDegrees.X*radians, RotationDegrees.Z*radians)
            * NumericsMatrix4x4.CreateTranslation(Position.ToNumerics());
    }
}

public enum LogLevel { Trace, Info, Warning, Error }

public static class Debug
{
    public static event Action<LogLevel, string>? Message;
    public static void Log(string message) => Write(LogLevel.Info, message);
    public static void Warning(string message) => Write(LogLevel.Warning, message);
    public static void Error(string message) => Write(LogLevel.Error, message);
    public static void Write(LogLevel level, string message)
    {
        ArgumentNullException.ThrowIfNull(message);
        Message?.Invoke(level, message);
        System.Diagnostics.Debug.WriteLine($"[Nexo3D:{level}] {message}");
    }
}

public static class Time
{
    private static float _deltaTime;
    private static double _elapsedTime;
    public static float DeltaTime => Volatile.Read(ref _deltaTime);
    public static double ElapsedTime => Volatile.Read(ref _elapsedTime);
    public static float TimeScale { get; set; } = 1f;
    internal static void Advance(float unscaledDelta)
    {
        var dt = Math.Clamp(unscaledDelta, 0f, 0.25f) * Math.Max(0, TimeScale);
        Volatile.Write(ref _deltaTime, dt);
        _elapsedTime += dt;
    }
}

public abstract class Behaviour
{
    public Entity? Entity { get; internal set; }
    public Transform Transform => Entity?.Transform ?? throw new InvalidOperationException("Behaviour is not attached to an entity.");
    public bool Enabled { get; set; } = true;
    public virtual void OnCreate() { }
    public virtual void OnEnable() { }
    public virtual void Update(float deltaTime) { }
    public virtual void FixedUpdate(float fixedDeltaTime) { }
    public virtual void OnDisable() { }
    public virtual void OnDestroy() { }
}

public sealed class Entity
{
    private readonly List<Behaviour> _behaviours = new();
    internal Entity(EntityId id, string name) { Id = id; Name = name; }
    public EntityId Id { get; }
    public string Name { get; set; }
    public bool Active { get; set; } = true;
    public Transform Transform { get; } = new();
    public IReadOnlyList<Behaviour> Behaviours => _behaviours;
    public T AddBehaviour<T>() where T : Behaviour, new()
    {
        var behaviour = new T { Entity = this };
        _behaviours.Add(behaviour);
        return behaviour;
    }
    public bool RemoveBehaviour(Behaviour behaviour)
    {
        if (!_behaviours.Remove(behaviour)) return false;
        behaviour.OnDestroy();
        behaviour.Entity = null;
        return true;
    }
}

public sealed class Scene
{
    private readonly Dictionary<EntityId, Entity> _entities = new();
    private ulong _nextId = 1;
    public string Name { get; set; } = "Untitled";
    public int Count => _entities.Count;
    public IEnumerable<Entity> Entities => _entities.Values;
    public Entity CreateEntity(string name = "Entity")
    {
        ArgumentException.ThrowIfNullOrWhiteSpace(name);
        var id = new EntityId(_nextId++);
        var entity = new Entity(id, name);
        _entities.Add(id, entity);
        return entity;
    }
    public bool TryGetEntity(EntityId id, out Entity? entity) => _entities.TryGetValue(id, out entity);
    public Entity? Find(string name) => _entities.Values.FirstOrDefault(e => e.Name == name);
    public bool DestroyEntity(EntityId id)
    {
        if (!_entities.Remove(id, out var entity)) return false;
        foreach (var behaviour in entity.Behaviours.ToArray()) entity.RemoveBehaviour(behaviour);
        return true;
    }
}

public sealed class ScriptRuntime
{
    private readonly Scene _scene;
    private readonly HashSet<Behaviour> _created = new();
    private readonly HashSet<Behaviour> _enabled = new();
    public ScriptRuntime(Scene scene) => _scene = scene ?? throw new ArgumentNullException(nameof(scene));
    public void Tick(float unscaledDeltaTime)
    {
        Time.Advance(unscaledDeltaTime);
        foreach (var entity in _scene.Entities.ToArray())
        foreach (var script in entity.Behaviours.ToArray())
        {
            if (!_created.Contains(script))
            {
                script.OnCreate();
                _created.Add(script);
            }
            if (!entity.Active || !script.Enabled)
            {
                if (_enabled.Remove(script)) script.OnDisable();
                continue;
            }
            if (_enabled.Add(script)) script.OnEnable();
            script.Update(Time.DeltaTime);
        }
    }
    public void FixedTick(float fixedDeltaTime)
    {
        if (!float.IsFinite(fixedDeltaTime) || fixedDeltaTime <= 0) throw new ArgumentOutOfRangeException(nameof(fixedDeltaTime));
        foreach (var entity in _scene.Entities)
            if (entity.Active)
                foreach (var script in entity.Behaviours)
                    if (script.Enabled) script.FixedUpdate(fixedDeltaTime);
    }
}
