// Copyright 2024 Rakin Rahman

#include <world.h>

#include <raylib.h>
#include <rcamera.h>

#include <cmath>

namespace {
/**
 * @brief Draw a circular crosshair at the center of the screen.
 */
void drawCrosshair() {
    int centerX { GetScreenWidth() / 2 };
    int centerY { GetScreenHeight() / 2 };
    DrawCircle(centerX, centerY, 5.0F, RED);
}

/**
 * @brief Convert world coordinates to grid coordinates.
 *
 * @param position
 *
 * @return grid coordinates.
 */
Vector3 worldToGrid(Vector3 position, int tileSize) {
    return { std::floor(position.x / tileSize),
             std::floor(position.y / tileSize),
             std::floor(position.z / tileSize) };
}
}  // namespace

World::World() {
    // Create 3D camera
    initializeCamera();
}

void World::play() {
    draw();
}

void World::initializeCamera() {
    // Define the camera to look into our 3d world
    m_camera.position = { 0.0F, 2.0F, 4.0F };  // Camera position
    m_camera.target = { 0.0F, 2.0F, 0.0F };    // Camera looking at point

    // Camera up vector (rotation towards target)
    m_camera.up = { 0.0F, 1.0F, 0.0F };

    m_camera.fovy = 60.0F;                     // Camera field-of-view Y
    m_camera.projection = CAMERA_PERSPECTIVE;  // Camera projection type
}

void World::handlePlayerMovement() {
}

void World::drawGround() {
    DrawGrid(HORIZONTAL_LIMIT, BLOCK_SIZE);
}

void World::draw() {
    UpdateCamera(&m_camera, CAMERA_FIRST_PERSON);

    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(m_camera);

    drawGround();

    EndMode3D();

    drawCrosshair();

    EndDrawing();
}
