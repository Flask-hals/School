#include "entity.h"
#include "player.h"

#pragma once

/** @class Fountain
 * @brief Klass för fontän som ger tillbaka liv när spelaren rör dess hitbox
 */

class Fountain: public Entity
{
    public:
        /** @brief Konstruktor för Fountain. Skickar alla parametrar till konstruktorn för Entity. */
        Fountain(sf::Vector2f cord, std::string object, sf::IntRect rect);

        /** @brief Default-konstruktor */
        Fountain();

        /** @brief Uppdateringsfunktion för spikarna.   
        * @param other Skickas in för att kolla efter kollisioner med andra Entity-objekt.
        */
        void update(const float &dt, Entity& other) override;
        
         /** @brief Kollisionshantering. Körs varje frame kollision sker med Player och ser till att spelaren får tillbaka liv en gång.
         * @param other Skickas in för att kunna manipulera spelarens health-värde. 
        */
        void handleCollision(Entity &other) override;
        
    private:
        bool fountainActive;  
};