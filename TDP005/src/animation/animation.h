#pragma once

#include "../common.h"

/**
 * @class Animation
 * @brief Styr animationen vid rörelse för objekt.
 */

class Animation
{
public:
    /**
     * @brief Konstruktor för Animation-klassen.
     *
     * @param texture Pekare till objektets texture för att hämta storleken.
     * @param imagecount Antalet rader och kolumner i sprite sheet.
     * @param switchTime Hur snabbt animationen växlar bild.
     */
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

    //~Animation();

    /**
     * @brief Uppdaterar animationen genom att loopa sprite sheet.
     *
     * @param row Den aktuella raden i sprite sheet.
     * @param startcolumn Startkolumn för animationen.
     * @param endcolumn Slutkolumn för att starta om loopen.
     * @param deltaTime Tiden som gått sedan senaste uppdateringen.
     * @param sprite Referens till spriten som ska uppdateras.
     */
    void update(int row, int startcolumn, int endcolumn, float deltaTime, sf::Sprite& sprite);


    sf::IntRect texRect; //Storleken för varje bild
private:
    sf::Vector2u currImage; //Nuvarande bild i sprite sheet

    float totalTime; // Sedan vi senast bytte bild
    float switchTime; //Hur lång tid det tar innan nästa bild
};