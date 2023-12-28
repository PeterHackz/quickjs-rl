#include <quickjs.h>
#include <raylib.h>

int main(void)
{
    const char *title = "Quick-rl Window Hello World";
    const char *text = "Hello World";

    InitWindow(800, 450, title);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(text, 400 - MeasureText(text, 20) / 2, 225, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}