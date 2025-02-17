#pragma once

#include "../main/gamestate.h"
#include "button.h"

/**
 * @class MenuState
 * @brief Representerar meny-tillståndet i spelet.
 * 
 * Hanterar huvudmenyn, inklusive rendering och interaktion med knappar.
 */
class MenuState : public State
{
public:
    /**
     * @brief Konstruktor för MenuState-klassen.
     * @param window Ett pekar till spelets renderingsfönster.
     * @param states En pekar till stacken med spelets olika tillstånd.
     */
    MenuState(sf::RenderWindow* window, std::stack<State*>* states);

    /**
     * @brief Destruktor för MenuState-klassen.
     */
    virtual ~MenuState();

    /**
     * @brief Uppdaterar användarinput i meny-tillståndet.
     * @param dt Delta-tiden som används för tidsbaserade uppdateringar.
     */
    void updateInput(const float& dt);

    /**
     * @brief Uppdaterar alla knappar i menyn.
     */
    void updateButtons();

    /**
     * @brief Uppdaterar meny-tillståndet.
     * @param dt Delta-tiden som används för uppdateringen.
     */
    void update(const float& dt);

    /**
     * @brief Renderar alla knappar.
     * @param target Renderingsmålet (standard är NULL).
     */
    void renderButtons(sf::RenderTarget* target = NULL);

    /**
     * @brief Renderar bakgrunden och alla element i menyn.
     * @param target Renderingsmålet (standard är NULL).
     */
    void render(sf::RenderTarget* target = NULL);

private:
    sf::RectangleShape background; ///< Rektangel för att rita bakgrunden.
    sf::Font font; ///< Typsnitt som används för text i menyn.

    std::map<std::string, Button*> buttons; ///< Karta över knappar i menyn.

    /**
     * @brief Initialiserar alla knappar i menyn.
     */
    void initButtons();

    /**
     * @brief Laddar och initialiserar typsnitt för text.
     */
    void initFonts();

    sf::Texture bgTexture; ///< Textur för menybakgrunden.

    /**
     * @brief Initialiserar bakgrunden för menyn.
     */
    void initBackground();
};
