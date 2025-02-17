#pragma once

#include "../ui/menu.h"

/**
 * @class Game
 * @brief Hanterar spelets huvudloop och övergripande logik.
 */
class Game
{
public:
    /**
     * @brief Konstruktor för Game-klassen.
     */
    Game();

    /**
     * @brief Destruktor för Game-klassen.
     */
    ~Game();

    /**
     * @brief Hanterar användarens input och händelser.
     */
    void handleEvents();

    /**
     * @brief Uppdaterar spelets logik.
     * 
     * Detta är en virtuell funktion som kan överskrivas av subklasser.
     */
    virtual void update();

    /**
     * @brief Renderar spelet.
     * 
     * Detta är en virtuell funktion som kan överskrivas av subklasser.
     */
    virtual void render();

    /**
     * @brief Kör spelets huvudloop.
     */
    void run();

    /**
     * @brief Avslutar applikationen och frigör resurser.
     */
    void endApplication();

    /**
     * @brief Uppdaterar delta-tiden (dt) som används för tidsstyrning.
     */
    void updateDt();

protected:
    sf::RenderWindow* window;  ///< Fönstret där spelet renderas.
    sf::Event event;           ///< Händelseobjekt för att fånga användarens input.
    sf::Clock dtClock;         ///< Klocka för att mäta delta-tid.

    float dt;                  ///< Delta-tid som används för tidsbaserad uppdatering.

    /**
     * @brief Initialiserar spelets fönster.
     */
    void initwindow();

    /**
     * @brief Initialiserar spelets olika tillstånd (states).
     */
    void initStates();

    std::stack<State*> states; ///< Stack som håller spelets olika tillstånd.
};

