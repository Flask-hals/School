#pragma once

#include "../common.h"

/**
 * @class Entity
 * @brief Basklass för alla objekt i spelet.
 *
 * Entity fungerar som en basklass som hanterar texturer, positionering och rendering för alla spelobjekt i spelet.
 */

class Entity
{
public:
    /**
     * @brief Konstruktor för Entity.
     *
     * Initierar ett spelobjekt genom att sätta textur, position (kordinater) och storlek (IntRect) baserat på vad som skickas in.
     * Om objektet är det första objektet som skapas, anropas loadTextures() för att ladda alla texturer i en map (textureResources).
     *
     * @param cord Kordinaterna där objektet ska skapas.
     * @param object Används för att hämta rätt textur för rätt objekt.
     * @param rect Styr hur stor del av sprite sheet som ska ritas ut.
     */
    Entity(sf::Vector2f cord, std::string object, sf::IntRect rect);

    /**
     * @brief Default konstruktor för Entity.
     *
     * Behövs för att stödja subklasser som kräver en standardkonstruktor.
     */
    Entity();
    virtual ~Entity();

    virtual void update(const float &dt, Entity &other) = 0;

    virtual void render(sf::RenderTarget *target);

    void setPosition(float x, float y);
    sf::FloatRect getGlobalBounds() const;
    virtual sf::Vector2f getPosition() const;

    /**
     * @brief Laddar in alla texturer i spelet.
     *
     * Funktionen är statisk för att varje objekt som initeras ska kunna dela på samma map av texturer.
     */
    static void loadTextures();

    /**
     * @brief Hämtar textur ut mapen textureResources baserat på namnet man skickar in.
     *
     * @param object Namnet på objektet man vill hämta texturen för.
     */
    virtual sf::Texture &getTextures(std::string const &object) const;

    /**
     * @brief Sätter texture till varje objekt's sprite, med rätt IntRect och position.
     *
     * @param cord Kordinaterna där objektet ska skapas.
     * @param object Används för att hämta rätt textur för rätt objekt.
     * @param rect Styr hur stor del av sprite sheeten som ska ritas ut.
     */
    void setTextures(sf::Vector2f cord, std::string object, sf::IntRect rect);

    /**
     * @brief Kontrollerar om objektet är aktivt och ska finnas kvar i spelet.
     *
     * Returnerar true om objektet är aktivt, annars false.
     *
     * @return bool Objektets status.
     */
    virtual bool checkActive();

    /**
     * @brief Hanterar kollisioner mellan två objekt.
     *
     * Virtuell funktion som måste implementeras av subklasser för att hantera specifik
     * kollision-logik.
     *
     * @param other Referens till ett annat objekt som kollisionen inträffar med.
     */
    virtual void handleCollision(Entity &other) = 0;
    /**
     * @brief Säger om objektet kan skjuta ett projektil.
     *
     * Standardimplementationen returnerar alltid false. Överskrids i subklasser.
     *
     * @return bool True om objektet kan skjuta ett projektil, annars false.
     */

    virtual bool shootProjectile();

protected:
    sf::Vector2f cord;
    std::string object;
    sf::Sprite sprite;
    sf::IntRect textureRect;
    static std::map<std::string, sf::Texture> textureResources;
    bool active;
};