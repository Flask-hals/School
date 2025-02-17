#pragma once

#include "enemy.h"

/**
 * @class ArrowEnemy
 * @brief Klass som representerar en pilbågs fiende i spelet.
 * 
 * Ärver från Enemy och använder funktioner från Enemy.
 * Innehåller funktioner för att hantera fiendens beteende och interaktion med spelaren.
 * 
 */

class ArrowEnemy : public Enemy
{
public:
    /**
     * @brief Konstruktor för ArrowEnemy.
     * 
     * Initierar pilbågs fienden med två olika hitboxes. En för när fienden kolliderar, den andra för när fienden kan upptäcka spelaren.
     * 
     * @param cord Kordinaterna där objektet ska skapas.
     * @param object Används för att hämta rätt textur för rätt objekt.
     * @param rect Styr hur stor del av sprite sheet som ska ritas ut.
     */
    ArrowEnemy(sf::Vector2f cord, std::string object, sf::IntRect rect);
    
    /**
     * @brief Projektilfiendernas uppdateringsfunktion.
     */
    void update(const float &dt, Entity& other) override;

    /**
     * @brief Uppdaterar så området där spelaren kan kollidera, alltid är satt på fienden.
     */
    void updateCollisionBox() override;
    /**
     * @brief Uppdaterar så området där spelaren kan bli upptäckt, alltid är satt på fienden.
     */
    void updateDetectBox() override;

    /**
     * @brief Hanterar om det ska skjutas en projektil eller inte.
     */
    bool shootProjectile() override;
private:
    float reductionFactorX; ///< Justeringsfaktor för X-axeln för detektionsboxen.
    float reductionFactorY; ///< Justeringsfaktor för Y-axeln för detektionsboxen.
    float lastAttack;
    
};