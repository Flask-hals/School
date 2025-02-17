#pragma once

#include "movablething.h"
#include "player.h"

/**
 * @class Enemy
 * @brief Klass som representerar en fiende i spelet, med funktioner för rörelse, attack och detektion.
 *
 * Ärver från MovableThing och innehåller funktioner för att hantera fiendens beteende och interaktion med spelaren.
 *
 */

class Enemy : public MovableThing
{
public:
    /**
     * @brief Konstruktor för Enemy.
     *
     * Används för att skapa en fiende och initiera dess position, textur och sprite sheet.
     *
     * @param cord Kordinaterna där fienden ska ritas ut.
     * @param object Används för att hämta rätt textur för rätt objekt.
     * @param rect Styr hur stor del av sprite sheeten som ska ritas ut.
     */
    Enemy(sf::Vector2f cord, std::string object, sf::IntRect rect);

    void handleCollision(Entity &other) override;
    /**
     * @brief Uppdaterar fiendens tillstånd.
     *
     * Denna metod kallas varje frame för att uppdatera fiendens rörelse, detektion och gravitation.
     *
     * @param dt deltatime, tiden sedan föregående frame.
     * @param other Används inte i den aktuella update, men måste finnas för att koppla ihop alla update funktioner.
     */
    // virtual void update(const float &dt, Entity& other) override;
    /**
     * @brief Aktiverar fienden när spelaren upptäcks.
     */
    virtual void detected();
    /**
     * @brief Uppdaterar så området där spelaren kan bli upptäckt, alltid är satt på fienden.
     */
    virtual void updateDetectBox();
    virtual sf::RectangleShape getDetectBox();
    virtual bool checkActivated();
    virtual sf::RectangleShape getCollisionBox();
    /**
     * @brief Uppdaterar så området där spelaren kan kollidera, alltid är fixerad på fienden.
     */
    virtual void updateCollisionBox();
    /**
     * @brief Ställer in gravitationens status för objektet.
     *
     * Aktiverar eller inaktiverar gravitationen för objektet baserat på den angivna bool-värdet.
     *
     * @param trueOrFalse Bool-värde som anger om gravitationen ska vara aktiv (true) eller inte (false).
     * @return bool Det nya gravitationsläget för objektet.
     */
    bool setGravity(bool trueOrFalse);
    /**
     * @brief Hanterar kollision mellan fienden och kartan.
     *
     * Flyttar fiendens sprite till en angiven position för att undvika överlappning
     * vid kollision med kartan.
     *
     * @param x Den nya horisontella positionen för fienden.
     * @param y Den nya vertikala positionen för fienden.
     */
    virtual void handleMapCollision(float x, float y);
    /**
     * @brief Kontrollerar om ett annat objekt har upptäckts av fienden.
     *
     * Jämför fiendens detectionbox med ett annat objekts spritebox.
     * Om en kollision upptäcks aktiveras fiendens "detekterad"-läge.
     *
     * @param other Referens till ett annat objekt, t.ex. spelaren.
     */
    void checkDetection(Entity &other);

protected:
    bool gravityActive{true};
    bool activated;                  ///< Om fienden har upptäckt spelaren (aktiverad).
    int steps;                       ///< Antal steg som fienden har tagit.
    int maxsteps;                    ///< Maximalt antal steg fienden får ta innan den vänder.
    sf::RectangleShape detectBox;    ///< Boxen som representerar fiendens detektionsområde.
    sf::RectangleShape collisionBox; ///< Boxen som representerar fiendens kollisionsområde.
    float collisionX;                ///< Justeringsfaktor för X-axeln för kollisionsboxen.
    float collisionY;                ///< Justeringsfaktor för Y-axeln för kollisionsboxen.
    float reductionFactorX;          ///< Justeringsfaktor för X-axeln för detektionsboxen.
    float reductionFactorY;          ///< Justeringsfaktor för Y-axeln för detektionsboxen.
};