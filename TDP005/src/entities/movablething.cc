#include "movablething.h"

MovableThing::MovableThing(sf::Vector2f cord, std::string object, sf::IntRect rect)
    : Entity{cord, object, rect}, health{100}, speed{35}, fallingspeed{}, gravity{1000}, isDead{false}, direction{1}, lastAttack{}, attackCooldown{10}
{}

MovableThing::MovableThing()
{}

void MovableThing::removeHealth(int hp)
{
    health -= hp;
    if (health <= 0)
        active = false;
}

bool MovableThing::canAttack()
{
    return lastAttack >= attackCooldown;
}

void MovableThing::handleCollision(Entity &other)
{}

void MovableThing::resetCooldown()
{
    lastAttack = 0;
}