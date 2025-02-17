#include "spikes.h"

Spikes::Spikes(sf::Vector2f coord, std::string object, sf::IntRect rect)
    : Entity(coord, object, rect){}

void Spikes::handleCollision(Entity& other)
{
    if (Player *player = dynamic_cast<Player*>(&other))
    {
        damageCheck = 0;
        player->removeHealth(10);    
        std::cout << "Player HP -10" << "\n";
    }
}

void Spikes::update(const float &dt, Entity& other)
{
    damageCheck += dt;
    if (damageCheck >= damageCoolDown && other.getGlobalBounds().intersects(getGlobalBounds()))
    {
        handleCollision(other);
    }
}