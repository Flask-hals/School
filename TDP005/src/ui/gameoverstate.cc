#include "gameoverstate.h"

GameOver::GameOver(sf::RenderWindow* window, std::stack<State*>* states)
: State (window, states)
{
    initBackground();
    initFonts();
    initButtons();
}

GameOver::~GameOver()
{
    auto it = buttons.begin();
    for (it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }
}



void GameOver::update(const float& dt)
{
    updateMousePositions();
    updateInput(dt);
    updateButtons();
}

void GameOver::render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = window;
    }

    target->setView(target->getDefaultView());

    target->draw(background);

    renderButtons(target);
}

void GameOver::updateInput(const float& dt)
{}

void GameOver::initFonts()
{
    if(!font.loadFromFile("src/assets/font.ttf"))
    {
        throw("ERROR: COULD NOT LOAD FONT");
    }
}

void GameOver::initButtons()       //Add buttons
{
    buttons["GAME_STATE"] = new Button(50, 50, 250, 75, 
                                    &font, "Restart Game", 
                                    sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
    this->buttons["EXIT_STATE"] = new Button(50, 125, 300, 75, 
                                    &this->font, "Return To Menu", 
                                    sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));    
}

void GameOver::updateButtons()
{
    /*Update all buttons in this state and handles the functionality*/
    for (auto &it : buttons)
    {
        it.second->update(mousePosView);
    }

    if (buttons["GAME_STATE"]->isPressed())
    {
        states->push(new GameState(window, states, "src/levels/map1.txt"));
    }
    
    //quit game
    if (buttons["EXIT_STATE"]->isPressed())
    {
        endState();
    }
}

void GameOver::renderButtons(sf::RenderTarget* target)
{
    for (auto &it : buttons)
    {
        it.second->render(target);
    }
}

void GameOver::initBackground()
{
    background.setSize(sf::Vector2f(800,600));
    
    if(!goTexture.loadFromFile("src/assets/game-over.jpg"))
    {
        throw "ERROR: game-over.jpg could not load in";
    }
    background.setTexture(&goTexture);
}