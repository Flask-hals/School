#include "door.h"

Door::Door(sf::Vector2f coord, std::string object, sf::IntRect rect)
    :   Entity(coord, object, rect), isActive{true} {}

Door::Door()
{}

void Door::handleCollision(Entity& other)
{
    if (isActive)
    {
        std::cout << "Map Clear" << "\n";
    } 
}

void Door::update(const float &dt, Entity& other)
{}