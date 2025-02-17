#include "projectile.h"

Projectile::Projectile(sf::Vector2f cord, std::string object, sf::IntRect rect)
    : Attack{cord, object, rect}, speed{100}, direction{}
{
}

void Projectile::update(const float &dt, Entity &other)
{
    if (checkActive())
    {
        if (direction.x == 0)
        {
            sf::Vector2f direction = other.getPosition() - getPosition();
            setDirection(direction);
        }
        else
        {
            sf::Vector2f currentPosition = getPosition();
            sf::Vector2f newPosition = currentPosition + direction * dt * (float)speed;

            setPosition(newPosition.x, newPosition.y);
            if (newPosition.x < 0 || newPosition.x > 5000 || newPosition.y < 0 || newPosition.y > 600)
            {
                active = false;
            }
            handleCollision(other);
        }
    }
}

void Projectile::setDirection(sf::Vector2f dir)
{
    direction = dir / std::sqrt(dir.x * dir.x + dir.y * dir.y);
}

void Projectile::handleCollision(Entity &other)
{
    sf::FloatRect playerHitBox = other.getGlobalBounds();
    sf::FloatRect arrowBox = sprite.getGlobalBounds();
    if (playerHitBox.intersects(arrowBox))
    {
        active = false;
        if (Player *player = dynamic_cast<Player*>(&other))
        {
            player->removeHealth(damage);
            std::cout << "Projectile - player HP -20" << "\n";
        }
    }
}