#ifndef DOOR_H
#define DOOR_H

#include "entity.h"
#include "player.h"

/**
 * @class Door
 * @brief Representerar en dörr i spelet.
 * 
 * Dörren är en typ av objekt som kan kollidera med spelaren och kan vara aktiv eller inaktiv.
 * Den hanterar också kollision med spelaren för att utlösa specifika händelser.
 */
class Door : public Entity
{
public:
    /**
     * @brief Konstruktor för Door-klassen.
     * 
     * Skapar en dörr på en angiven position, med en specifik objektsträng och kollisionsrektangel.
     * @param cord Positionen (x, y) för dörren i världen.
     * @param object En sträng som identifierar dörrens objekt (kan användas för att identifiera dörrens typ).
     * @param rect En rektangel som definierar kollisionsområdet för dörren.
     */
    Door(sf::Vector2f cord, std::string object, sf::IntRect rect);

    /**
     * @brief Standardkonstruktor för Door-klassen.
     * 
     * Skapar en dörr med standardvärden (t.ex. standardposition och storlek).
     */
    Door();

    /**
     * @brief Dörrens uppdateringsfunktion.
     */
    void update(const float &dt, Entity& other) override;

    /**
     * @brief Hanterar kollisionen mellan dörren och spelaren.
     * 
     * När spelaren kolliderar med dörren kan den aktiveras eller utlösa en händelse beroende på
     * dörrens nuvarande status.
     * @param other Spelaren som kolliderar med dörren.
     */
    void handleCollision(Entity& other) override;

private:
    bool isActive; ///< Anger om dörren är aktiv eller inte (kan påverka om den kan öppnas eller interageras med).
};

#endif
