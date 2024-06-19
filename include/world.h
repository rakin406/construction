// Copyright 2024 Rakin Rahman

#ifndef INCLUDE_WORLD_H_
#define INCLUDE_WORLD_H_

#include <raylib.h>

#include <vector>

/**
 * @brief This class contains the main functions of the game.
 */
class World {
public:
    // Constants
    static constexpr int MAX_VOXELS { 1000 };
    static constexpr float TILE_SIZE { 1.0F };
    static constexpr int HORIZONTAL_LIMIT { 320 };
    static constexpr int VERTICAL_LIMIT { 320 };

    struct Block {
        bool occupied {};
        // Vector3 position {};
    };

    struct Voxel {
        Vector3 position {};
        Color color {};
        bool active {};
    };

    /**
     * @brief Default constructor for World initialization.
     */
    World();

    /**
     * @brief Play the world.
     */
    void play();

private:
    Camera3D m_camera {};
    // std::vector<std::vector<std::vector<Block>>> m_grid;
    std::vector<Voxel> m_voxels;

    /**
     * @brief Initialize 3D camera.
     */
    void cameraInit();

    /**
     * @brief Initialize grid with all blocks unoccupied.
     */
    void gridInit();

    int getInactiveVoxelIndex();

    int findVoxelIndexAtPosition(Vector3 position);

    /**
     * @brief Place a block at the given position.
     *
     * @param position
     */
    void placeBlock(Vector3 position);

    /**
     * @brief Get world coordinates from position on the screen.
     *
     * @return world coordinates.
     */
    Vector3 getWorldCoordsFromScreen();

    /**
     * @brief Draw the whole world.
     */
    void draw();

    /**
     * @brief Check if a position is within grid bounds.
     *
     * @param position
     *
     * @return boolean.
     */
    static bool isWithinGrid(Vector3 position);

    /**
     * @brief Convert world coordinates to grid coordinates.
     *
     * @param position
     *
     * @return grid coordinates.
     */
    static Vector3 worldToGrid(Vector3 position);

    /**
     * @brief Draw ground/floor.
     */
    static void drawGround();
};

#endif  // INCLUDE_WORLD_H_
