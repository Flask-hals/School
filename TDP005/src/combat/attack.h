#pragma once

#include "../entities/movablething.h"

/**
 * @class Attack
 * @brief Samlade funktioner för de olika attackerna i spelet.
 * 
 * Ärver från MovableThing.
 */

class Attack : public MovableThing
{
public:
    /**
     * @brief Konstruktor för Attack.
     * 
     * Används för att projektiler ska kunna sätta en egen position, storlek och utseende.
     * 
     * @param cord Kordinaterna där attacken ska ritas ut.
     * @param object Används för att hämta rätt textur för rätt objekt.
     * @param rect Styr hur stor del av sprite sheeten som ska ritas ut.
     */
    Attack(sf::Vector2f cord, std::string object, sf::IntRect rect);

    /**
     * @brief Default konstruktor för Attack.
     * 
     * Används främst för att kunna skapa tomma Attack objekt i andra klasser.
     */
    Attack();

protected:
    int damage;

};