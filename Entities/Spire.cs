using Raylib_cs;
using System.Numerics;

namespace KesefStory.Entities;

internal record Sprite(
    Texture2D Texture,
    Rectangle Source,
    Rectangle Hitbox,
    Vector2 Origin
)
{
    public Rectangle Hitbox { get; set; } = Hitbox;
}

internal record DisplayName(string Text, int FontSize, Font? CustomFont = null);

class Player(
    Sprite sprite,
    DisplayName displayName,
    float speed = 5f
)
{
    public Sprite Sprite { get; } = sprite;
    public DisplayName DisplayName { get; } = displayName;
    public float Speed { get; set; } = speed;

    public void MoveLeft(int screenWidth)
    {
        Sprite.Hitbox = Sprite.Hitbox with
        {
            X = Math.Clamp(Sprite.Hitbox.X - Speed, 0, screenWidth - Sprite.Hitbox.Width)
        };
    }

    public void MoveRight(int screenWidth)
    {
        Sprite.Hitbox = Sprite.Hitbox with
        {
            X = Math.Clamp(Sprite.Hitbox.X + Speed, 0, screenWidth - Sprite.Hitbox.Width)
        };
    }
}
