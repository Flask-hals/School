#include "arrowenemy.h"

ArrowEnemy::ArrowEnemy(sf::Vector2f cord, std::string object, sf::IntRect rect)
    : Enemy{cord, object, rect}, reductionFactorX{10.f}, reductionFactorY{10.f}, lastAttack{10}
{
    updateDetectBox();
    updateCollisionBox();
}

void ArrowEnemy::update(const float &dt, Entity& other)
{
    lastAttack += dt;
    updateDetectBox();
    updateCollisionBox();
    checkDetection(other);
    if (gravityActive)
    {
        sprite.move(0, fallingspeed * dt);
        fallingspeed += gravity * dt;
    }
    if (other.getGlobalBounds().intersects(collisionBox.getGlobalBounds()))
    {
        handleCollision(other);
    } 
}

void ArrowEnemy::updateCollisionBox()
{
    sf::FloatRect coll = sprite.getGlobalBounds();

    collisionBox.setSize(sf::Vector2f(
        coll.width * collisionX,
        coll.height * collisionY));

    collisionBox.setPosition(
        sprite.getPosition().x - sprite.getOrigin().x + (coll.width - collisionBox.getSize().x) / 2.f,
        sprite.getPosition().y - sprite.getOrigin().y + (coll.height - collisionBox.getSize().y) / 2.f);
}

void ArrowEnemy::updateDetectBox()
{
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();

    detectBox.setSize(sf::Vector2f(
        spriteBounds.width * reductionFactorX,
        spriteBounds.height * reductionFactorY));

    detectBox.setPosition(
        sprite.getPosition().x - sprite.getOrigin().x + (spriteBounds.width - detectBox.getSize().x) / 2.f,
        sprite.getPosition().y - sprite.getOrigin().y + (spriteBounds.height - detectBox.getSize().y) / 2.f);
}

bool ArrowEnemy::shootProjectile()
{
    if (lastAttack >= attackCooldown && checkActivated())
    {
        lastAttack = 0;
        return true;
    }
    else
    {
        return false;
    }
}