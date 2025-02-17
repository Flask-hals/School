#include "swordenemy.h"

SwordEnemy::SwordEnemy(sf::Vector2f cord, std::string object, sf::IntRect rect)
    : Enemy{cord, object, rect}, animation{&getTextures("swordenemy"), {8, 5}, 0.1f}, velocity{0.f, 0.f}, reductionFactorX{5.f}, reductionFactorY{5.f}, attackCooldown{2}
{
    updateDetectBox();
    updateCollisionBox();
}

void SwordEnemy::update(const float &dt, Entity &other)
{
    lastAttack += dt;
    handleMovement(dt, other.getPosition());
    updateDetectBox();
    updateCollisionBox();
    checkDetection(other);
    attack(other);
    if (other.getGlobalBounds().intersects(collisionBox.getGlobalBounds()))
    {
        handleCollision(other);
    } 
}

void SwordEnemy::handleMovement(const float &dt, sf::Vector2f other)
{
    if (!activated)
    {
        sprite.setTextureRect(sf::IntRect(0, 0, 64, 90));
        if (steps < maxsteps)
        {
            animation.update(2, 0, 7, dt, sprite);
            steps++;
        }
        else
        {
            direction *= -1;
            sprite.setScale(direction, 1.f);
            steps = 0;
        }
    }
    else
    {
        animation.update(2, 0, 7, dt, sprite);
        if (other.x > sprite.getPosition().x)
        {
            sprite.setScale(1.f, 1.f);
            direction = 1;
        }
        else
        {
            sprite.setScale(-1.f, 1.f);
            direction = -1;
        }
    }
    velocity.x = direction * speed;
    sprite.move(velocity * dt);
    if (gravityActive)
    {
        sprite.move(0, fallingspeed * dt);
        fallingspeed += gravity * dt;
    }
}

void SwordEnemy::attack(Entity &other)
{
    if (other.getGlobalBounds().intersects(getGlobalBounds()) && lastAttack >= attackCooldown)
    {
        if (Player *player = dynamic_cast<Player*>(&other))
        {
            player->removeHealth(10);
            resetCooldown();
            std::cout << "Enemy sword -10" << std::endl;
        }
    } 
}