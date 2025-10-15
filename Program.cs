using Raylib_cs;
using System.Numerics;

namespace KesefStory;

internal static class Program
{
    public static void Main()
    {
        var screenWidth = 800;
        var screenHeight = 400;
        Raylib.InitWindow(screenWidth, screenHeight, "Kesef Story");

        var nicknameFontSize = 12;
        var heeboNicknameFontSize = 15;
        var heeboTextFontSize = 25;

        var kesefHatufim = Raylib.LoadTexture("Assets/kesef-hatufim.png");
        var kesefSource = new Rectangle(0, 0, kesefHatufim.Width, kesefHatufim.Height);
        var kesefHitbox = new Rectangle(100, 300, kesefHatufim.Width / 6, kesefHatufim.Height / 6);
        var kesefOrigin = new Vector2(kesefHitbox.Width / 2, kesefHitbox.Height / 2);
        var kesefNicknameLabel = "KesefHatufim";

        var orwell = Raylib.LoadTexture("Assets/orwell.png");
        var orwellSource = new Rectangle(0, 0, orwell.Width, orwell.Height);
        var orwellHitbox = new Rectangle(650, 290, orwell.Width / 2, orwell.Height / 2);
        var orwellOrigin = new Vector2(orwellHitbox.Width / 2, orwellHitbox.Height / 2);

        var orwellNicknameLabel = new string("אורוול".ToCharArray().Reverse().ToArray());

        var orwelTextLabel = new string("אתה חטיף בסבתא מיזולדה, כלב כן כלב".ToCharArray().Reverse().ToArray());

        int nicknamePad = (int)(nicknameFontSize * 1.1f);

        int[] hebrewCodepoints = new int[(128 - 32 + 1) + (0x05ff - 0x0590 + 1)];
        int cpidx = 0;
        for (int c = 32; c < 128; c++) hebrewCodepoints[cpidx++] = c;
        for (int c = 0x0590; c <= 0x05ff; c++) hebrewCodepoints[cpidx++] = c;

        var heeboFont = Raylib.LoadFontEx("Fonts/Heebo/Heebo-Regular.ttf", 32, hebrewCodepoints, cpidx);

        while (!Raylib.WindowShouldClose())
        {
            Raylib.BeginDrawing();
            Raylib.ClearBackground(Color.Black);

            if (Raylib.IsKeyDown(KeyboardKey.Left))
            {
                kesefHitbox.X = Math.Clamp(kesefHitbox.X - 1, 0, screenWidth - kesefHitbox.Width);
            }
            if (Raylib.IsKeyDown(KeyboardKey.Right))
            {
                kesefHitbox.X = Math.Clamp(kesefHitbox.X + 1, 0, screenWidth);
            }

            Raylib.DrawTexturePro(kesefHatufim, kesefSource, kesefHitbox, kesefOrigin, 0, Color.White);
            int kesefTw = Raylib.MeasureText(kesefNicknameLabel, nicknameFontSize);
            int kesefLx = (int)(kesefHitbox.X - kesefTw / 2);
            int kesefLy = (int)(kesefHitbox.Y + kesefHitbox.Height / 2 + nicknamePad);
            Raylib.DrawText(kesefNicknameLabel, kesefLx, kesefLy, nicknameFontSize, Color.White);

            Raylib.DrawTexturePro(orwell, orwellSource, orwellHitbox, orwellOrigin, 0, Color.White);
            float orwellTw = Raylib.MeasureTextEx(heeboFont, orwellNicknameLabel, heeboNicknameFontSize, 1.0f).X;
            int orwellLx = (int)(orwellHitbox.X - orwellTw / 2);
            int orwellLy = (int)(orwellHitbox.Y + orwellHitbox.Height / 2 + nicknamePad);
            Raylib.DrawTextEx(heeboFont, orwellNicknameLabel, new Vector2(orwellLx, orwellLy), heeboNicknameFontSize, 1.0f, Color.White);

            var orwellTextFontSize = (float)heeboTextFontSize;
            var orwellTextM = Raylib.MeasureTextEx(heeboFont, orwelTextLabel, orwellTextFontSize, 1.0f);
            if (orwellTextM.X > screenWidth * 0.95f) // allow 5% margin
            {
                float scale = (screenWidth * 0.95f) / orwellTextM.X;
                orwellTextFontSize *= scale;
                orwellTextM = Raylib.MeasureTextEx(heeboFont, orwelTextLabel, orwellTextFontSize, 1.0f);
            }
            int orwellTextLx = (int)(orwellHitbox.X - orwellHitbox.Width - orwellTextM.X / 2);
            int orwellTextLy = (int)(orwellHitbox.Y - orwellHitbox.Height - (orwellTextM.Y * 0.4f));
            Raylib.DrawTextEx(heeboFont, orwelTextLabel, new Vector2(orwellTextLx, orwellTextLy), orwellTextFontSize, 1.0f, Color.White);


            Raylib.DrawText("Hello, handicapped!", 12, 12, 20, Color.White);

            Raylib.EndDrawing();
        }

        Raylib.CloseWindow();
    }
}
