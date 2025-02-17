#pragma once

#include "enemy.h"
#include "../animation/animation.h"

/**
 * @class SwordEnemy
 * @brief Representerar melee fiender i spelet.
 * 
 * Ärver från Enemy och använder mycket av Enemy's funktioner.
 * SwordEnemy hanterar specifika egenskaper såsom rörelse mönster och hitbox.
 */

class SwordEnemy : public Enemy
{
public:
    /**
     * @brief Konstruktor för SwordEnemy.
     * 
     * Initierar melee fienden med två olika hitboxes. En för när fienden kolliderar, den andra för när fienden kan upptäcka spelaren.
     * 
     * @param cord Kordinaterna där objektet ska skapas.
     * @param object Används för att hämta rätt textur för rätt objekt.
     * @param rect Styr hur stor del av sprite sheet som ska ritas ut.
     */
    SwordEnemy(sf::Vector2f cord, std::string object, sf::IntRect rect);

    /**
     * @brief Uppdaterar fiendens funktioner varje frame.
     * 
     * Funktionen kallar på fiendens funktioner som uppdaterar fiendens rörelsemönster och hitboxar.
     * 
     * @param dt deltatime, tiden sedan föregående frame.
     * @param other Positionen av spelaren.
     */
    void update(const float &dt, Entity& other) override;

    /**
     * @brief Uppdaterar fiendens rörelsemönster varje frame.
     * 
     * Beräknar fiendens rörelsemönster baserat på om den är aktiverad eller inte, icke aktiverad så patrullerar fienden.
     * Aktiverad så jagar fienden spelaren.
     * 
     * @param dt deltatime, tiden sedan föregående frame.
     * @param other Positionen av spelaren.
     */
    void handleMovement(const float &dt, sf::Vector2f other);

    /**
     * @brief Hanterar svärdfiendernas atacker.
     */
    void attack(Entity& other);


private:
    float reductionFactorX;
    float reductionFactorY;

    Animation animation;
    sf::Vector2f velocity;
    float attackCooldown;
};