#ifndef YouWinSTATE_H
#define YouWinSTATE_H

#include "../main/gamestate.h"
#include "button.h"

/**
 * @class YouWin
 * @brief Representerar spelets Game Over-tillstånd.
 * 
 * Hanterar visning och interaktion med Game Over-menyn.
 */
class YouWin : public State
{
public:
    /**
     * @brief Konstruktor för YouWin-klassen.
     * @param window Ett pekar till det renderingsfönster som används.
     * @param states En pekar till stacken som innehåller alla spelets tillstånd.
     */
    YouWin(sf::RenderWindow* window, std::stack<State*>* states);

    /**
     * @brief Destruktor för YouWin-klassen.
     */
    ~YouWin();

    /**
     * @brief Uppdaterar användarinput för Game Over-tillståndet.
     * @param dt Delta-tiden som används för tidsbaserade uppdateringar.
     */
    void updateInput(const float& dt);

    /**
     * @brief Uppdaterar alla knappar i Game Over-menyn.
     */
    void updateButtons();

    /**
     * @brief Uppdaterar Game Over-tillståndet.
     * @param dt Delta-tiden som används för tidsbaserade uppdateringar.
     */
    void update(const float& dt);

    /**
     * @brief Renderar alla knappar på skärmen.
     * @param target Renderingsmålet (standard är NULL).
     */
    void renderButtons(sf::RenderTarget* target = NULL);

    /**
     * @brief Renderar bakgrunden och alla element i Game Over-tillståndet.
     * @param target Renderingsmålet (standard är NULL).
     */
    void render(sf::RenderTarget* target = NULL);

private:
    sf::RectangleShape background; ///< Rektangel för att rita bakgrunden.
    sf::Font font;                 ///< Typsnitt som används för text i Game Over-menyn.

    std::map<std::string, Button*> buttons; ///< En lista över knappar i Game Over-menyn.

    /**
     * @brief Initialiserar alla knappar som används i Game Over-menyn.
     */
    void initButtons();

    /**
     * @brief Laddar och initialiserar typsnitt för text.
     */
    void initFonts();

    sf::Texture goTexture; ///< Textur som används för bakgrunden.

    /**
     * @brief Initialiserar bakgrunden för Game Over-tillståndet.
     */
    void initBackground();
};

#endif
