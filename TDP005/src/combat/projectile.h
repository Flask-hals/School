#pragma once

#include "attack.h"
#include "../entities/player.h"

/**
 * @class Projectile
 * @brief Representerar projektiler i spelet.
 * 
 * Ärver från Attack, använder Attack's dealDamage funktion, samt skriver över damage variabeln.
 * Projectile hanterar specifika egenskaper såsom direction för projektiler, samt om dem ska vara aktiva eller ej.
 */

class Projectile : public Attack
{
public:
    /**
     * @brief Konstruktor för Projectile.
     * 
     * Initierar projektilen med startkordinater, storlek och utseende.
     * 
     * @param cord Kordinaterna där projektilen ska skapas.
     * @param object Används för att hämta rätt textur för rätt objekt.
     * @param rect Styr hur stor del av sprite sheeten som ska ritas ut.
     */
    Projectile(sf::Vector2f cord, std::string object, sf::IntRect rect);

    /**
     * @brief Uppdaterar projektilens rörelse varje frame.
     * 
     * @param dt deltatime, tiden sedan föregående frame.
     * @param other Positionen av spelaren.
     */
    void update(const float &dt, Entity& other) override;

    /**
     * @brief Skapar pilens riktning.
     * 
     * Pilens riktning baseras på avståndet mellan spelaren och fienden (där projektilen skapas).
     * 
     * @param dir Avståndet mellan spelaren och fienden.
     */
    void setDirection(sf::Vector2f dir);

    /**
     * @brief Kollisionshantering för projektilerna.
     * 
     * @param other Referens till ett annat objekt som kollisionen inträffar med.
     */
    void handleCollision(Entity &other) override;

private:
    sf::Vector2f direction;
    double speed;
};