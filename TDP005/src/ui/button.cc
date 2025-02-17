#include "button.h"
//#include "state.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text,
         sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
         : font{font}, idleColor{idleColor}, hoverColor{hoverColor}, activeColor{activeColor}
{
    buttonState = BTN_IDLE;

    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));

    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(50);            //ändra storlek på texten
    
    this->text.setPosition(
        shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,      //Fixa egen position på knappen (kanske måste ta globalbounds / 2.f)
        shape.getPosition().y + (shape.getGlobalBounds().height / 20.f) - this->text.getGlobalBounds().height / 10.f
    );

    shape.setFillColor(idleColor);
}

const bool Button::isPressed() const
{
    if (buttonState == BTN_ACTIVE)
    {
        return true;
    }
    return false;
}

void Button::render(sf::RenderTarget* target)
{
    target->draw(shape);
    target->draw(text);
}

void Button::update(const sf::Vector2f mousePos)
{
    /* Uppdate the booleans for hover and pressed */
    //Idle
    buttonState = BTN_IDLE;
    //Hover
    if (shape.getGlobalBounds().contains(mousePos))
    {
        buttonState = BTN_HOVER;
        //Pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            buttonState = BTN_ACTIVE;
        }
    }

    switch (buttonState)
    {
    case BTN_IDLE:
        shape.setFillColor(idleColor);
        break;

    case BTN_HOVER:
        shape.setFillColor(hoverColor);
        break;

    case BTN_ACTIVE:
        shape.setFillColor(activeColor);
        break;
    }
}