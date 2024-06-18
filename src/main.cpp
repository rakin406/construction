// Copyright 2024 Rakin Rahman

#include <constants.h>
#include <world.h>

#include <raylib.h>

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.data());

    DisableCursor();

    SetTargetFPS(60);

    World world {};

    // Detect window close button or ESC key
    while (!WindowShouldClose()) {
        world.play();
    }

    CloseWindow();

    return 0;
}
