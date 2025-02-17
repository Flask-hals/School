#pragma once
#include "../common.h"

/**
 * @enum button_states
 * @brief Enum som representerar de olika tillstånden en knapp kan ha.
 * 
 * BTN_IDLE: Knappen är i sitt viloläge.
 * BTN_HOVER: Muspekaren är över knappen.
 * BTN_ACTIVE: Knappen är nedtryckt.
 */
enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

/**
 * @class Button
 * @brief En klass som representerar en knapp på skärmen.
 * 
 * Knappen kan vara i olika tillstånd (idle, hover, active) och kan renderas på skärmen samt uppdateras baserat på musens position.
 */
class Button
{
public:
    /**
     * @brief Konstruktor för Button-klassen.
     * 
     * Initialiserar en knapp med de angivna egenskaperna.
     * @param x X-positionen för knappen.
     * @param y Y-positionen för knappen.
     * @param width Bredden på knappen.
     * @param height Höjden på knappen.
     * @param font Ett pekar till fonten som ska användas för texten på knappen.
     * @param text Texten som ska visas på knappen.
     * @param idleColor Färgen för knappen i sitt viloläge.
     * @param hoverColor Färgen för knappen när muspekaren är över den.
     * @param activeColor Färgen för knappen när den är nedtryckt.
     */
    Button(float x, float y, float width, float height, sf::Font* font, std::string text,
         sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

    /**
     * @brief Renderar knappen på skärmen.
     * @param target Renderingsmålet (fönstret där knappen ska ritas).
     */
    void render(sf::RenderTarget* target);

    /**
     * @brief Uppdaterar knappen baserat på musens position.
     * @param mousePos Musens aktuella position.
     */
    void update(const sf::Vector2f mousePos);

    /**
     * @brief Kontrollerar om knappen har blivit nedtryckt.
     * @return True om knappen är nedtryckt, annars false.
     */
    const bool isPressed() const;

private:
    short unsigned buttonState; ///< Aktuellt tillstånd för knappen (idle, hover, active).

    sf::RectangleShape shape; ///< Form för knappen (rektangel).
    sf::Font* font; ///< Pekar till fonten som används för knappen.
    sf::Text text; ///< Texten som visas på knappen.

    sf::Color idleColor; ///< Färg för knappen när den är i sitt viloläge.
    sf::Color hoverColor; ///< Färg för knappen när muspekaren är över den.
    sf::Color activeColor; ///< Färg för knappen när den är nedtryckt.
};
