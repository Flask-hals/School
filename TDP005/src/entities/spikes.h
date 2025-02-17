#include "entity.h"
#include "player.h"

#pragma once

/** @class Spikes
 * @brief Klass för spikar som ärver från Entity
 */  
class Spikes: public Entity
{
    public:
        /** @brief Konstruktor för Spikes. Skickar alla parametrar till konstruktorn för Entity*/
        Spikes(sf::Vector2f cord, std::string object, sf::IntRect rect);

        /** @brief Kollisionshantering. Körs varje frame kollision sker med Player och ser till att spelaren tar skada när detta händer
         * @param other Skickas in för att kunna manipulera spelarens health-värde
         * @param dt Tiden sedan föregående frame 
        */
        void handleCollision(Entity& other) override;

        /** @brief Uppdateringsfunktion för spikarna
        * @param other Skickas för att kolla efter kollisioner med andra Entity-objekt.
        */
        void update(const float &dt, Entity& other) override;
    private:
        float damageCoolDown{1.0}; //Decides how long it takes before player takes damage again
        float damageCheck{1.0};  //This value will increase each frame player is in contact with spikes     
};