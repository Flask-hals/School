#pragma once

#include "entity.h"

/**
 * @class MovableThing
 * @brief Representerar alla rörliga objekt i spelet.
 * 
 * MovableThing agerar basklass för alla rörliga objekt såsom fiender, spelare och projektiler.
 * Klassen har ett antal funktioner som rör liv och tidsbaserade händelser, som objekten använder.
 * Klassen agerar också länk mellan alla objekt och basklassen Entity.
 */

class MovableThing : public Entity
{
public:
    /**
     * @brief Konstruktor för MovableThing.
     *
     * Initierar ett objekt genom att skicka värden såsom textur, position (kordinater) och storlek (IntRect) till Entity's konstruktor.
     * Konstruktorn sätter även ett antal värden som inte skickas till Entity, dessa datamedlemmar används av flera subklasser.
     *
     * @param cord Kordinaterna där objektet ska skapas.
     * @param object Används för att hämta rätt textur för rätt objekt.
     * @param rect Styr hur stor del av sprite sheeten som ska ritas ut.
     */
    MovableThing(sf::Vector2f cord, std::string object, sf::IntRect rect);

    /**
     * @brief Default konstruktor för MovableThing.
     *
     * Behövs för att stödja subklasser som kräver en standardkonstruktor.
     */
    MovableThing();

    /**
     * @brief Tar bort liv hos objekten.
     *
     * @param hp Förkortning för healthpoints, (liv).
     */
    virtual void removeHealth(int hp);
     /**
     * @brief Säger om objekt kan attackera.
     */
    virtual bool canAttack();
     /**
     * @brief Hanterar kollition.
     *
     * @param other Referens till ett annat objekt som kollisionen inträffar med.
     */
    virtual void handleCollision(Entity &other) override;
    /**
     * @brief Nollställer cooldown för när en attack kan ske.
     */
    virtual void resetCooldown();

protected:
    bool isDead;
    int health;
    double speed;
    float fallingspeed;
    float gravity;
    int direction;
    float lastAttack;
    float attackCooldown;
};