#include "animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
    : switchTime(switchTime), totalTime(0.0f), currImage(0, 0)
{
    texRect.width = texture->getSize().x / float(imageCount.x);
    texRect.height = texture->getSize().y / float(imageCount.y);
}

void Animation::update(int row, int startcolumn, int endcolumn, float deltaTime, sf::Sprite& sprite)
{
    totalTime += deltaTime;

    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currImage.x++;

        if (currImage.x >= endcolumn)
        {
            currImage.x = startcolumn;
        }
    }

    texRect.left = currImage.x * texRect.width;
    texRect.top = row * texRect.height;

    sprite.setTextureRect(texRect);
}