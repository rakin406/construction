// Copyright 2024 Rakin Rahman

#ifndef INCLUDE_WORLD_H_
#define INCLUDE_WORLD_H_

#include <raylib.h>

/**
 * @brief This class contains the main functions of the game.
 */
class World {
public:
    /**
     * @brief Default constructor for World initialization.
     */
    World();

    /**
     * @brief Play the world.
     */
    void play();

private:
    Camera3D m_camera {};  // Initialize camera

    /**
     * @brief Initialize 3D camera.
     */
    void initializeCamera();

    /**
     * @brief Detect key and move player according to direction.
     */
    void handlePlayerMovement();

    /**
     * @brief Draw ground/floor.
     */
    void drawGround();

    /**
     * @brief Draw the whole world.
     */
    void draw();
};

#endif  // INCLUDE_WORLD_H_
