#include "player.h"

Player::Player(sf::Vector2f cord, std::string object, sf::IntRect rect)
    : MovableThing{cord, object, rect}, speed{200}, lastAttack{}, attackCooldown{0.5f}, canJump{true}, jumpHeight{200.f}, animation{&getTextures("player"), {8, 5}, 0.1f},
      direction{1}, velocity{0.f, 0.f}, reductionFactorX{0.01f}, reductionFactorY{0.01f}
{
    updateHitbox();
}

void Player::update(const float &dt, Entity &other)
{
    if (Player *player = dynamic_cast<Player *>(&other))
    {
        if (canJump && canAttack())
        {
            sprite.setTextureRect(sf::IntRect(0, 0, 64, 90));
        }
        lastAttack += dt;
        velocity.x = 0.f;
        updateHitbox();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        {
            if (canAttack())
            {
                sprite.setTextureRect(sf::IntRect(432, 270, 64, 90));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if (sprite.getPosition().x > 5)
            {
                movement(-1, dt);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            movement(1, dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
        {
            sprite.setTextureRect(sf::IntRect(496, 360, 64, 90));
            velocity.y = -sqrtf(2.0f * gravity * jumpHeight);
            canJump = false;
        }

        velocity.y += gravity * dt;

        float groundLevel = 800 - (sprite.getGlobalBounds().height / 2.f);
        if (sprite.getPosition().y >= groundLevel)
        {
            active = false;
        }

        sprite.move(velocity * dt);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && canAttack())
    {
        lastAttack += dt;
        attack(other);
    }
}

void Player::addHealth(double hp)
{
    health += hp;
    if (health > 100)
        health = 100;
}

void Player::updateHitbox()
{
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();

    playerHitbox.setSize(sf::Vector2f(
        spriteBounds.width * reductionFactorX,
        spriteBounds.height * reductionFactorY));

    playerHitbox.setPosition(
        sprite.getPosition().x - sprite.getOrigin().x + (spriteBounds.width - playerHitbox.getSize().x) / 2.f,
        sprite.getPosition().y - sprite.getOrigin().y + (spriteBounds.height - playerHitbox.getSize().y) / 2.f);
}

sf::RectangleShape Player::getHitbox()
{
    return playerHitbox;
}

void Player::handleCollision(sf::RectangleShape &other)
{
    if (playerHitbox.getGlobalBounds().left < other.getGlobalBounds().left)
    {
        sprite.setPosition(getPosition().x - (other.getGlobalBounds().width + 1), getPosition().y);
    }
    else if (playerHitbox.getGlobalBounds().left > other.getGlobalBounds().left)
    {
        sprite.setPosition(getPosition().x + (other.getGlobalBounds().width + 1), getPosition().y);
    }
    updateHitbox();
}

void Player::resetCooldown()
{
    lastAttack = 0;
}

bool Player::canAttack()
{
    return lastAttack >= attackCooldown;
}

void Player::movement(int direction, const float &dt)
{
    animation.update(2, 0, 7, dt, sprite);
    velocity.x = direction * speed;
    if (sprite.getScale().x > 0)
    {
        sprite.setScale(direction, 1.f);
    }
    else
    {
        sprite.setScale(direction, 1.f);
    }
}

void Player::changeVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
}

sf::Vector2f Player::getVelocity()
{
    return velocity;
}

void Player::changeJump()
{
    canJump = true;
}

void Player::attack(Entity &other)
{
    if (getGlobalBounds().intersects(other.getGlobalBounds()))
    {
        if (Enemy *enemy = dynamic_cast<Enemy *>(&other))
        {
            std::cout << "Player attack! -50" << std::endl;
            enemy->removeHealth(50);
            resetCooldown();
        }
    }
}