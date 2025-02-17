#include "state.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states)
    : window{window}, states{states}
{
    quit = false;
}

State::~State()
{}

void State::endState()
{
    quit = true;
}

const bool & State::getQuit() const
{
    return quit;
}

void State::updateMousePositions()
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(*window);
    mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}