#pragma once

#include "movablething.h"
#include "../animation/animation.h"
#include "../world/TileMap.h"
#include "enemy.h"

/**
 * @class Player
 * @brief Representerar spelaren i spelet.
 * 
 * Ärver från MovableThing och innehåller funktioner för att hantera spelarens rörelse, interaktion samt funktionalitet som hälsa, attack och kollisioner.
 */

class Player : public MovableThing
{
public:
    /**
     * @brief Konstruktor för Player.
     * 
     * Används för att skapa en spelare och initiera dess position, textur och sprite sheet.
     * 
     * @param cord Kordinaterna där spelaren ska ritas ut.
     * @param object Används för att hämta rätt textur för rätt objekt.
     * @param rect Styr hur stor del av sprite sheeten som ska ritas ut.
     */
    Player(sf::Vector2f cord, std::string object, sf::IntRect rect);

    /**
     * @brief Uppdaterar spelarens tillstånd.
     * 
     * Denna metod kallas varje frame för att uppdatera spelarensrörelse, gravitation och animation. 
     * 
     * @param dt deltatime, tiden sedan föregående frame.
     */
    void update(const float &dt, Entity& other) override;

    /**
     * @brief Lägger till liv hos spelaren.
     * 
     * Specifik funktion för spelaren.
     * 
     * @param hp Förkortning för healthpoints, (liv).
     */
    void addHealth(double hp);

    /**
     * @brief Kollisionshantering mellan fiende och spelare.
     * 
     * Knuffar spelaren bakåt, från det håll spelaren kolliderar.
     * 
     * @param other Området för objektet som spelaren kolliderar med.
     */
    void handleCollision(sf::RectangleShape &other);
    
    /**
     * @brief Hämtar spelarens hitbox för kollision.
     * 
     * @return Spelarens aktuella hitbox som en sf::RectangleShape.
     */
    sf::RectangleShape getHitbox();

    /**
     * @brief Nollställer cooldown för när en attack kan ske.
     */
    void resetCooldown() override;

    /**
     * @brief Uppdaterar spelarens hitbox.
     * 
     * Området där spelaren kan kollidera ska alltid vara fixerad på spelaren.
     */
    void updateHitbox();

    /**
     * @brief Kontrollerar om spelaren kan attackera.
     * 
     * @return returnerar true ifall spelaren kan attackera.
     */
    bool canAttack() override;

    /**
     * @brief Styr spelarens rörelser.
     * 
     * @param direction Vilket håll spelaren går åt.
     * @param dt deltatime, tiden sedan föregående frame.
     */
    void movement(int direction, const float& dt);

    /**
     * @brief Ändrar spelarens hastighet.
     * 
     * @param x Förändring i X-led.
     * @param y Förändring i Y-led.
     */
    void changeVelocity(float x, float y);

    /**
     * @brief Hämtar spelarens nuvarande hastighet.
     * 
     * @return Spelarens hastighet som en sf::Vector2f.
     */
    sf::Vector2f getVelocity();

    /**
     * @brief Ändrar så spelaren kan hoppa.
     */
    void changeJump();
    
    /**
     * @brief Hanterar spelarens attack.
     */
    void attack(Entity &other);

private:
    int speed; ///< Spelarens hastighet
    sf::RectangleShape playerHitbox; ///< Spelarens kollisionsruta.
    float reductionFactorX; ///< Justeringsfaktor för X-axeln för detektionsboxen.
    float reductionFactorY; ///< Justeringsfaktor för Y-axeln för detektionsboxen.

    float lastAttack; ///< Tid sedan senaste attacken.
    float attackCooldown; ///< Hur lång tid spelaren inte kan attackera på.

    float jumpHeight; ///< Höjden spelaren kan hoppa.

    Animation animation; ///< Animation för spelaren.
    int direction; ///< Vilket håll spelaren går åt.
    bool canJump; ///< Säger om spelaren kan hoppa eller inte.
    sf::Vector2f velocity; ///< Spelarens rörelsehastighet
};