// Copyright 2024 Rakin Rahman

#include <constants.h>

#include <raylib.h>

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.data());

    DisableCursor();

    SetTargetFPS(60);

    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        // Update
        // TODO(rakin): Update your variables here

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20,
                 LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
