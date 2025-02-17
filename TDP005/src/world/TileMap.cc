#include "TileMap.h"

TileMap::TileMap()
{
    tileHitbox.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
}

TileMap::~TileMap()
{
}

void  TileMap::update()
{
}

void TileMap::loadfile(std::string currentMap)
{
    std::ifstream openfile(currentMap);

    if (!openfile.is_open())
    {
        std::cerr << "ERROR: COULD NOT OPEN " + currentMap + "\n";
    }

    openfile >> tileLocation;

    if (!tileTexture.loadFromFile(tileLocation)) 
    {
    std::cerr << "Error: Could not load tile texture from " << tileLocation << "\n";
    }

    tileSprite.setTexture(tileTexture);
    std::string line;
    while (std::getline(openfile, line))
    {
        std::vector<std::pair<sf::Vector2i, bool>> row; // Add collision flag
        std::istringstream iss(line);
        std::string cell;
        while (std::getline(iss, cell, ' ')) {
            if (cell.size() >= 3 && isdigit(cell[0]) && isdigit(cell[2])) 
            {
                bool collidable = (cell.size() > 4 && cell[4] == '1');
                row.emplace_back(sf::Vector2i(cell[0] - '0', cell[2] - '0'), collidable);
            } 
            else 
            {
                row.emplace_back(sf::Vector2i(-1, -1), false);
            }
        }
        map.push_back(row);
        
    }
}

bool TileMap::checkCollision(const sf::FloatRect& bounds) const
{
    for (size_t y = 0; y < map.size(); ++y)
    {
        for (size_t x = 0; x < map[y].size(); ++x)
        {
            const auto& [tilePos, collidable] = map[y][x];

            if (!collidable || tilePos.x == -1 || tilePos.y == -1)
                continue;

            sf::FloatRect tileBounds(
                static_cast<float>(x * TILE_SIZE),
                static_cast<float>(y * TILE_SIZE),
                TILE_SIZE, TILE_SIZE
            );

            if (tileBounds.intersects(bounds))
            {
                return true; // Kollision detekterad
            }
        }
    }
    return false; // Ingen kollision
}

int TileMap::getRowCount()
{
    return map.size();
}

int TileMap::getColumnCount(int row)
{
    if (row < map.size())
    {
        return map[row].size();
    }
    return 1;
}

std::pair<sf::Vector2i, bool> TileMap::getTile(size_t x, size_t y)
{
    if (y < map.size() && x < map[y].size()) {
        return map[y][x];
    }
    return std::pair<sf::Vector2i, bool>(sf::Vector2i(-1, -1), false);
}


void TileMap::render(sf::RenderTarget& target)
{
   for (size_t y = 0; y < map.size(); ++y)
   {
        for (size_t x = 0; x < map[y].size(); ++x)
        {
            const auto& [tilePos, collidable] = map[y][x];

            if (tilePos.x == -1 || tilePos.y == -1)
                continue; // Skip invalid tiles

            tileSprite.setPosition(static_cast<float>(x * TILE_SIZE),static_cast<float>(y * TILE_SIZE) );
            tileSprite.setTextureRect(sf::IntRect(tilePos.x * TILE_SIZE, tilePos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE));

            target.draw(tileSprite);
        }
   }
}

std::vector<std::vector<std::pair<sf::Vector2i, bool>>> TileMap::getMap()
{
    return map;
}