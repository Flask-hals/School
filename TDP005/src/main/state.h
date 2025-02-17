#pragma once

#include "../entities/entity.h"

/**
 * @class State
 * @brief En abstrakt basklass för olika spel-tillstånd.
 * 
 * State-klassen innehåller gemensam funktionalitet och gränssnitt 
 * som alla spel-tillstånd ärver och implementerar.
 */
class State
{
public:
    /**
     * @brief Konstruktor för State-klassen.
     * @param window Ett pekar till spelets renderingsfönster.
     * @param states En pekar till stacken med spelets tillstånd.
     */
    State(sf::RenderWindow* window, std::stack<State*>* states);

    /**
     * @brief Virtuell destruktor för State-klassen.
     */
    virtual ~State();

    /**
     * @brief Hämtar tillståndets avslutningsflagga.
     * @return En konstant referens till bool-värdet som indikerar om tillståndet ska avslutas.
     */
    const bool& getQuit() const;

    /**
     * @brief Sätter tillståndets avslutningsflagga.
     */
    void endState();

    /**
     * @brief Uppdaterar muspositionerna i spelets fönster och vy.
     */
    virtual void updateMousePositions();

    /**
     * @brief Virtuell funktion för att uppdatera användarinput.
     * @param dt Delta-tid för tidsbaserade uppdateringar.
     */
    virtual void updateInput(const float& dt) = 0;

    /**
     * @brief Virtuell funktion för att uppdatera tillståndets logik.
     * @param dt Delta-tid för tidsbaserade uppdateringar.
     */
    virtual void update(const float& dt) = 0;

    /**
     * @brief Virtuell funktion för att rendera tillståndets innehåll.
     * @param target Renderingsmålet (standard är NULL).
     */
    virtual void render(sf::RenderTarget* target = NULL) = 0;

protected:
    std::stack<State*>* states; ///< En pekare till stacken med spelets olika tillstånd.
    bool quit; ///< Flagga som indikerar om tillståndet ska avslutas.

    std::vector<sf::Texture> textures; ///< Vektor som innehåller texturer som används i tillståndet.
    sf::RenderWindow* window; ///< Pekar till spelets renderingsfönster.

    sf::Vector2i mousePosScreen; ///< Musens position på skärmen.
    sf::Vector2i mousePosWindow; ///< Musens position i fönstret.
    sf::Vector2f mousePosView; ///< Musens position i den aktuella vyn.
};
