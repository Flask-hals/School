#pragma once
#include "../common.h"



/**
 * @class TileMap
 * @brief Representerar en tilemap (rutnät av tiles) för att skapa spelets värld.
 * 
 * TileMap hanterar rendering, uppdatering och kollisionskontroll av tiles som utgör spelvärlden.
 */
class TileMap
{
public:
    /**
     * @brief Konstruktor för TileMap-klassen.
     * 
     * Initierar en tom tilemap.
     */
    TileMap();

    /**
     * @brief Destruktor för TileMap-klassen.
     */
    virtual ~TileMap();

    /**
     * @brief Renderar tilemapen på det givna målet.
     * @param target Renderingsmålet (fönstret där tilemapen ska ritas).
     */
    void render(sf::RenderTarget& target);

    /**
     * @brief Uppdaterar tilemapen. 
     * Detta kan inkludera uppdateringar av tile-egenskaper eller andra logiska förändringar.
     */
    void update();

    /**
     * @brief Laddar tilemap-data från en fil.
     * Detta inkluderar att läsa filens innehåll och skapa tilemapens struktur.
     */
    void loadfile(std::string currentMap);

    /**
     * @brief Kontrollerar om en given rektangel kolliderar med tilemapens tiles.
     * @param bounds En `sf::FloatRect` som representerar objektets kollisionsområde.
     * @return `true` om kollision upptäcks, annars `false`.
     */
    bool checkCollision(const sf::FloatRect& bounds) const;

    /**
     * @brief Hämtar antalet rader i tilemapen.
     * @return Antalet rader i tilemapen.
     */
    int getRowCount();

    /**
     * @brief Hämtar antalet kolumner i en viss rad i tilemapen.
     * @param row Radens index.
     * @return Antalet kolumner i den specificerade raden.
     */
    int getColumnCount(int row);

    /**
     * @brief Hämtar information om en specifik tile i tilemapen.
     * @param x X-koordinat för tilen.
     * @param y Y-koordinat för tilen.
     * @return Ett par som innehåller tilens position och en bool som anger om tile är kollisionsbar.
     */
    std::pair<sf::Vector2i, bool> getTile(size_t x, size_t y);

    /**
     * @brief Hämtar hela tilemapen som en tvådimensionell vektor.
     * @return En tvådimensionell vektor som representerar tilemapen där varje tile är ett par 
     *         med position och kollisionsstatus.
     */
    std::vector<std::vector<std::pair<sf::Vector2i, bool>>> getMap();

    //std::string getCurrentMap();

protected:
    std::string tileLocation; ///< Filens plats för tile-texturen.
    sf::Texture tileTexture; ///< Textur som används för att rendera tiles.
    sf::Sprite tileSprite; ///< Sprite för att visa tile.
    sf::RectangleShape tileHitbox; ///< Rektangel för att definiera tilens kollisionsområde.
    std::vector<std::vector<std::pair<sf::Vector2i, bool>>> map; ///< En tvådimensionell vektor som lagrar tilemapen.

    const int TILE_SIZE{32}; ///< Storleken på varje tile (i pixlar).
    
};
