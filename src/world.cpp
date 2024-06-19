// Copyright 2024 Rakin Rahman

#include <world.h>

#include <raylib.h>
#include <raymath.h>
#include <rcamera.h>

#include <cmath>
#include <iostream>

namespace {
/**
 * @brief Draw a circular crosshair at the center of the screen.
 */
void drawCrosshair() {
    int centerX { GetScreenWidth() / 2 };
    int centerY { GetScreenHeight() / 2 };
    DrawCircle(centerX, centerY, 5.0F, RED);
}

bool vector3Equals(Vector3 v1, Vector3 v2) {
    return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}
}  // namespace

World::World() {
    cameraInit();
    // gridInit();
    m_voxels.resize(MAX_VOXELS);
    for (std::size_t i = 0; i < MAX_VOXELS; ++i) {
        m_voxels[i].position = { 0, 0, 0 };
        m_voxels[i].color = { 0, 0, 0, 0 };
        m_voxels[i].active = false;
    }
}

void World::play() {
    draw();
}

void World::cameraInit() {
    // Define the camera to look into our 3d world
    m_camera.position = { 0.0F, 2.0F, 4.0F };  // Camera position
    m_camera.target = { 0.0F, 2.0F, 0.0F };    // Camera looking at point

    // Camera up vector (rotation towards target)
    m_camera.up = { 0.0F, 1.0F, 0.0F };

    m_camera.fovy = 60.0F;                     // Camera field-of-view Y
    m_camera.projection = CAMERA_PERSPECTIVE;  // Camera projection type
}

// void World::gridInit() {
//     m_grid.resize(HORIZONTAL_LIMIT);
//
//     for (std::size_t x = 0; x < HORIZONTAL_LIMIT; ++x) {
//         m_grid[x].resize(VERTICAL_LIMIT);
//
//         for (std::size_t y = 0; y < VERTICAL_LIMIT; ++y) {
//             m_grid[x][y].resize(HORIZONTAL_LIMIT);
//
//             for (std::size_t z = 0; z < HORIZONTAL_LIMIT; ++z) {
//                 m_grid[x][y][z].occupied = false;
//             }
//         }
//     }
// }
//
// void World::placeBlock(Vector3 position) {
//     if (isWithinGrid(position)) {
//         m_grid.at(static_cast<std::size_t>(position.x))
//             .at(static_cast<std::size_t>(position.y))
//             .at(static_cast<std::size_t>(position.z))
//             .occupied = true;
//     }
// }
//
// Vector3 World::getWorldCoordsFromScreen() {
//     Vector2 mousePos { GetMousePosition() };
//     Ray ray { GetMouseRay(mousePos, m_camera) };
//
//     Vector3 hitPosition { -1, -1, -1 };
//     bool hit { false };
//
//     // Check for intersection with existing blocks or ground plane
//     for (std::size_t x = 0; x < HORIZONTAL_LIMIT && !hit; ++x) {
//         for (std::size_t y = 0; y < VERTICAL_LIMIT && !hit; ++y) {
//             for (std::size_t z = 0; z < HORIZONTAL_LIMIT && !hit; ++z) {
//                 if (m_grid[x][y][z].occupied) {
//                     BoundingBox box {
//                         { x * TILE_SIZE, y * TILE_SIZE, z * TILE_SIZE },
//                         { (x + 1) * TILE_SIZE, (y + 1) * TILE_SIZE,
//                           (z + 1) * TILE_SIZE }
//                     };
//
//                     RayCollision collision { GetRayCollisionBox(ray, box) };
//                     if (collision.hit) {
//                         hit = true;
//                         hitPosition = { static_cast<float>(x),
//                                         static_cast<float>(y),
//                                         static_cast<float>(z) };
//                     }
//                 }
//             }
//         }
//     }
//
//     return hitPosition;
// }
//
// bool World::isWithinGrid(Vector3 position) {
//     return (position.x >= 0 && position.x < HORIZONTAL_LIMIT &&
//             position.y >= 0 && position.y < VERTICAL_LIMIT && position.z >= 0
//             && position.z < HORIZONTAL_LIMIT);
// }
//

int World::getInactiveVoxelIndex() {
    for (std::size_t i = 0; i < MAX_VOXELS; ++i) {
        if (!m_voxels[i].active) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int World::findVoxelIndexAtPosition(Vector3 position) {
    for (std::size_t i = 0; i < MAX_VOXELS; ++i) {
        if (m_voxels[i].active &&
            vector3Equals(m_voxels[i].position, position)) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void World::drawGround() {
    DrawGrid(HORIZONTAL_LIMIT, TILE_SIZE);
}

void World::draw() {
    // Update
    UpdateCamera(&m_camera, CAMERA_FREE);

    // Ray ray { GetMouseRay(GetMousePosition(), m_camera) };

    // Remove voxel
    // if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    //     for (std::size_t i = 0; i < MAX_VOXELS; ++i) {
    //         if (m_voxels[i].active &&
    //             GetRayCollisionBox(ray, { m_voxels[i].position,
    //                                       Vector3Add(m_voxels[i].position,
    //                                                  { 1.0F, 1.0F, 1.0F }) })
    //                 .hit) {
    //             m_voxels[i].active = false;
    //             break;
    //         }
    //     }
    // }

    // Add voxel
    // if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
    //     for (std::size_t i = 0; i < MAX_VOXELS; ++i) {
    //         if (m_voxels[i].active &&
    //             GetRayCollisionBox(ray, { m_voxels[i].position,
    //                                       Vector3Add(m_voxels[i].position,
    //                                                  { 1.0F, 1.0F, 1.0F }) })
    //                 .hit) {
    //             Vector3 newPosition { m_voxels[i].position };
    //             newPosition.x += 1.0F;
    //
    //             auto newIndex { static_cast<std::size_t>(
    //                 getInactiveVoxelIndex()) };
    //             if (static_cast<int>(newIndex) != -1) {
    //                 m_voxels[newIndex].position = newPosition;
    //                 m_voxels[newIndex].color = {
    //                     static_cast<unsigned char>(GetRandomValue(0, 255)),
    //                     static_cast<unsigned char>(GetRandomValue(0, 255)),
    //                     static_cast<unsigned char>(GetRandomValue(0, 255)), 255
    //                 };
    //                 m_voxels[newIndex].active = true;
    //             }
    //             break;
    //         }
    //     }
    // }

    // Draw
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(m_camera);

    drawGround();

    for (std::size_t i = 0; i < MAX_VOXELS; ++i) {
        if (m_voxels[i].active) {
            DrawCube(m_voxels[i].position, 1.0F, 1.0F, 1.0F, m_voxels[i].color);
            DrawCubeWires(m_voxels[i].position, 1.0F, 1.0F, 1.0F, BLACK);
        }
    }

    EndMode3D();

    drawCrosshair();

    EndDrawing();
}
