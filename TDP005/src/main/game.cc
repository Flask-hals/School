#include "game.h"

using namespace sf;

void Game::initwindow()
{
    window = new RenderWindow(VideoMode(800, 600), "Test");

    while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
    } // sätter blackscreen tills man trycker på ngåot (kanske byta ut)
}

Game::Game()
{
    initwindow();
    initStates();
}

Game::~Game()
{
    delete window;

    while (!states.empty())
    {
        delete states.top();
        states.pop();
    }
}

void Game::handleEvents()
{
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        }
    }
}

void Game::update()
{
    handleEvents();
    if (!states.empty())
    {
        states.top()->update(dt);

        if (states.top()->getQuit())
        {
            states.top()->endState();
            delete states.top();
            states.pop();
        }
    }
    // applications end
    else
    {
        endApplication();
        window->close();
    }
}

void Game::render()
{
    window->clear();
    if (!states.empty())
    {
        states.top()->render();
    }

    window->display();
}

void Game::endApplication()
{
    std::cout << "Ending application" << std::endl;
}

void Game::initStates()
{
    states.push(new MenuState(window, &states));
}

void Game::updateDt()
{
    /*Updates dt with the time it takes to update and render one frame*/
    dt = dtClock.restart().asSeconds();
}

void Game::run()
{
    while (window->isOpen())
    {
        updateDt();
        update();
        render();
    }
}