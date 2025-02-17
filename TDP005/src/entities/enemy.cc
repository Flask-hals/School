#include "enemy.h"

Enemy::Enemy(sf::Vector2f cord, std::string object, sf::IntRect rect)
    : MovableThing{cord, object, rect}, steps{}, maxsteps{9000}, activated{false}, collisionX{0.3f}, collisionY{0.3f}, reductionFactorX{5.f}, reductionFactorY{5.f}
{}

void Enemy::handleCollision(Entity &other)
{
    if (Player *player = dynamic_cast<Player*>(&other))
    {
        player->removeHealth(10);
        std::cout << "Player HP -10" << "\n";
        player->handleCollision(collisionBox);
    } 
}

bool Enemy::setGravity(bool trueOrFalse)
{
    return gravityActive = trueOrFalse;
}

bool Enemy::checkActivated()
{
    return activated;
}

void Enemy::detected()
{
    activated = true;
}

sf::RectangleShape Enemy::getDetectBox()
{
    return detectBox;
}

sf::RectangleShape Enemy::getCollisionBox()
{
    return collisionBox;
}

void Enemy::updateCollisionBox()
{
    sf::FloatRect coll = sprite.getGlobalBounds();

    collisionBox.setSize(sf::Vector2f(
        coll.width * collisionX,
        coll.height * collisionY));

    collisionBox.setPosition(
        sprite.getPosition().x - sprite.getOrigin().x + (coll.width - collisionBox.getSize().x) / 2.f,
        sprite.getPosition().y - sprite.getOrigin().y + (coll.height - collisionBox.getSize().y) / 2.f);
}


void Enemy::updateDetectBox()
{
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();

    detectBox.setSize(sf::Vector2f(
        spriteBounds.width * reductionFactorX,
        spriteBounds.height * reductionFactorY));

    detectBox.setPosition(
        sprite.getPosition().x - sprite.getOrigin().x + (spriteBounds.width - detectBox.getSize().x) / 2.f,
        sprite.getPosition().y - sprite.getOrigin().y + (spriteBounds.height - detectBox.getSize().y) / 2.f);
}

void Enemy::handleMapCollision(float x, float y)
{
    sprite.setPosition(x, y);
}

void Enemy::checkDetection(Entity& other)
{
    sf::FloatRect playerBox = other.getGlobalBounds();
    sf::FloatRect enemyBox = getDetectBox().getGlobalBounds();
    if (playerBox.intersects(enemyBox))
    {
        detected();
    }
}