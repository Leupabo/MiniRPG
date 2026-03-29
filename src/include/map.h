/**
 * @file map.h
 * @brief Definition of the Map class and related structures for game maps
 */

#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

/**
 * @def MAX_MAP_WIDTH
 * @brief Maximum width of a map in tiles
 */
#define MAX_MAP_WIDTH 100

/**
 * @def MAX_MAP_HEIGHT
 * @brief Maximum height of a map in tiles
 */
#define MAX_MAP_HEIGHT 100

/**
 * @enum TileType
 * @brief Enumeration of different types of tiles in the game map
 */
enum TileType {
    TILE_FLOOR = '.',   ///< Floor tile that can be walked on
    TILE_WALL = '#',    ///< Wall tile that blocks movement
    TILE_TREE = 'T',    ///< Tree tile that blocks movement
    TILE_WATER = 'W',   ///< Water tile that blocks movement
    TILE_PORTAL = 'P',  ///< Portal tile that allows transition between maps
};

/**
 * @struct Portal
 * @brief Structure representing a portal between maps
 */
struct Portal {
    int sourceX, sourceY;  ///< Coordinates of the portal in the source map
    int targetMapId;       ///< ID of the target map
    int targetX, targetY;  ///< Coordinates where the player will appear in the target map
};

/**
 * @class Map
 * @brief Class representing a game map
 * 
 * The Map class handles loading, storing, and providing access to the game map data,
 * including tiles and portals.
 */
class Map {
private:
    int id;                                     ///< Unique identifier for the map
    int width, height;                          ///< Dimensions of the map
    TileType tiles[MAX_MAP_HEIGHT][MAX_MAP_WIDTH]; ///< 2D array of tiles
    std::vector<Portal> portals;                ///< Collection of portals on the map

public:
    /**
     * @brief Default constructor
     */
    Map();

    /**
     * @brief Constructor that loads a map from a file
     * @param filename Path to the map file
     */
    Map(const std::string& filename);
    
    /**
     * @brief Destructor
     */
    ~Map();
    
    /**
     * @brief Loads a map from a file
     * @param filename Path to the map file
     * @return true if the map was loaded successfully, false otherwise
     */
    bool loadFromFile(const std::string& filename);
        
    /**
     * @brief Loads a map by its ID
     * @param mapId ID of the map to load
     * @return true if the map was loaded successfully, false otherwise
     */
    bool loadFromId(int mapId);

    /**
     * @brief Gets the ID of the map
     * @return Map ID
     */
    int getId() const;
    
    /**
     * @brief Gets the width of the map
     * @return Map width in tiles
     */
    int getWidth() const;
    
    /**
     * @brief Gets the height of the map
     * @return Map height in tiles
     */
    int getHeight() const;
    
    /**
     * @brief Gets the tile type at specified coordinates
     * @param x X coordinate
     * @param y Y coordinate
     * @return Tile type at the specified position
     */
    TileType getTile(int x, int y) const;
    
    /**
     * @brief Gets the character representation of the tile at specified coordinates
     * @param x X coordinate
     * @param y Y coordinate
     * @return Character representing the tile
     */
    char getTileChar(int x, int y) const;
    
    /**
     * @brief Sets the tile type at specified coordinates
     * @param x X coordinate
     * @param y Y coordinate
     * @param tile New tile type
     */
    void setTile(int x, int y, TileType tile);
    
    /**
     * @brief Sets the tile at specified coordinates using a character representation
     * @param x X coordinate
     * @param y Y coordinate
     * @param tileChar Character representing the new tile type
     */
    void setTile(int x, int y, char tileChar);

    /**
     * @brief Checks if a tile can be walked on
     * @param x X coordinate
     * @param y Y coordinate
     * @return true if the tile is walkable, false otherwise
     */
    bool isWalkable(int x, int y) const;
    
    /**
     * @brief Checks if a tile is a portal
     * @param x X coordinate
     * @param y Y coordinate
     * @return true if the tile is a portal, false otherwise
     */
    bool isPortal(int x, int y) const;

    /**
     * @brief Adds a portal to the map
     * @param sourceX X coordinate of the portal in the source map
     * @param sourceY Y coordinate of the portal in the source map
     * @param targetMapId ID of the target map
     * @param targetX X coordinate where the player will appear in the target map
     * @param targetY Y coordinate where the player will appear in the target map
     */
    void addPortal(int sourceX, int sourceY, int targetMapId, int targetX, int targetY);
    
    /**
     * @brief Gets the portal at specified coordinates
     * @param x X coordinate
     * @param y Y coordinate
     * @return Pointer to the portal if one exists at the specified position, nullptr otherwise
     */
    const Portal* getPortalAt(int x, int y) const;

    /**
     * @brief Regression test for the Map class
     * @return 0 if all tests pass, a positive number otherwise
     */
    static int regressionTest();
};

#endif // MAP_H