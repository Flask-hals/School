#include "menu.h"



MenuState::MenuState(sf::RenderWindow* window, std::stack<State*>* states)
: State (window, states)
{
    this->initBackground();
    this->initFonts();
    this->initButtons();
}

MenuState::~MenuState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

void MenuState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateInput(dt);

    this->updateButtons();
}

void MenuState::render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = this->window;
    }

    target->setView(target->getDefaultView());

    target->draw(this->background);

    this->renderButtons(target);
}

void MenuState::updateInput(const float& dt)
{
    
}

void MenuState::initFonts()
{
    if(!this->font.loadFromFile("src/assets/font.ttf"))
    {
        throw("ERROR: could not load font.ttf");
    }
}

void MenuState::initButtons()       //Add buttons
{
    this->buttons["GAME_STATE"] = new Button(500, 50, 250, 75, 
                                    &this->font, "Start Game", 
                                    sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
    this->buttons["EXIT_STATE"] = new Button(650, 125, 100, 75, 
                                    &this->font, "Quit", 
                                    sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

void MenuState::updateButtons()
{
    /*Update all buttons in this state and handles the functionality*/
    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    if (this->buttons["GAME_STATE"]->isPressed())
    {
        this->states->push(new GameState(this->window, this->states, "src/levels/map1.txt"));
    }
    
    //quit game
    if (this->buttons["EXIT_STATE"]->isPressed())
    {   
        //this->quit = true;
        this->endState();
    }
}

void MenuState::renderButtons(sf::RenderTarget* target)
{
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void MenuState::initBackground()
{
    this->background.setSize(sf::Vector2f
                            (static_cast<float>(this->window->getSize(). x), 
                            static_cast<float>(this->window->getSize(). y)));
    
    if(!this->bgTexture.loadFromFile("src/assets/bgrund.jpg"))
    {
        throw std::invalid_argument("ERROR: bgrund.jpg could not load in");
    }
    this->background.setTexture(&this->bgTexture);


}