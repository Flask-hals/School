#include "entity.h"

std::map<std::string, sf::Texture> Entity::textureResources;


Entity::Entity(sf::Vector2f cord, std::string object, sf::IntRect rect)
    : cord{cord}, object{object}, textureRect{rect}, active{true}
{
    if (textureResources.empty())
    {
        loadTextures();
    }
    setTextures(cord, object, textureRect);
}

Entity::Entity()
{}

Entity::~Entity()
{}

void Entity::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

sf::FloatRect Entity::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}

sf::Vector2f Entity::getPosition() const
{
    return sprite.getPosition();
}

void Entity::render(sf::RenderTarget *target)
{
    target->draw(sprite);
}

void Entity::loadTextures()
{
    sf::Texture texture;

    if (texture.loadFromFile("src/assets/knight.png"))
    {
        textureResources["player"] = texture;
    }
    if (texture.loadFromFile("src/assets/enemy.png"))
    {
        textureResources["swordenemy"] = texture;
        textureResources["arrowenemy"] = texture;
        textureResources["projectile"] = texture;
    }
    if (texture.loadFromFile("src/assets/fountain.png"))
    {
        textureResources["fountain"] = texture;
    }
    if(texture.loadFromFile("src/assets/door.png"))
    {
        textureResources["door"] = texture;
    }
    if (texture.loadFromFile("src/assets/spikes.png"))
    {
        textureResources["spikes"] = texture;
    }
}

sf::Texture& Entity::getTextures(std::string const& object) const
{
    auto it = textureResources.find(object);
    if (it == textureResources.end())
    {
        throw std::runtime_error("Texture with key '" + object + "' not found.");
    }
    return it->second;
}

void Entity::setTextures(sf::Vector2f cord, std::string object, sf::IntRect rect)
{
    sprite.setTexture(getTextures(object));
    sprite.setTextureRect(textureRect);
    sprite.setOrigin(rect.width / 2.f, rect.height / 2.f);
    sprite.setPosition(cord);
}

bool Entity::checkActive()
{
    return active;
}

bool Entity::shootProjectile()
{
    return false;
}