#include "fountain.h"

Fountain::Fountain(sf::Vector2f coord, std::string object, sf::IntRect rect)
    :   Entity(coord, object, rect), fountainActive{true}{}

Fountain::Fountain()
{}

void Fountain::update(const float &dt, Entity& other)
{
    if (other.getGlobalBounds().intersects(getGlobalBounds()))
    {
        handleCollision(other);
    } 
}

void Fountain::handleCollision(Entity& other)
{
    if (fountainActive)
    {
        if (Player *player = dynamic_cast<Player*>(&other))
        {
            player->addHealth(30);
            fountainActive = false;
            std::cout << "Player HP +30" << "\n";
        }
    } 
}