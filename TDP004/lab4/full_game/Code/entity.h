#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "grid.h"

/*
  Typdeklaration för att representera en position i kartan. Går i diskreta steg där varje steg representerar
  en ruta.
 */
using Point = sf::Vector2i;

/*
  Basklass som representerar alla ritbara rörliga objekt i spelet. Har härledda klasser för pacman och spöken. 
 */
class Entity : public sf::ConvexShape
{
public:
    Entity(sf::Vector2f const& start_position, Grid& grid, int speed, sf::Color const& color);
    virtual ~Entity() = default;

    /*
      Uppdaterar objektets position. Varje Entity väljer en position en ruta framåt eller bakåt i x-
      eller y-led och flyttar sig sedan med en jämn hastighet dit. När den når den rutan väljer den
      en ny ruta och börjar om. Sättet den väljer en ruta sker med select_new_target() och
      implementeras av den härledda klassen.
     */
    virtual void update();

protected:
    bool at_target_position() const;
    virtual void move_forward();
    
    /*
      Uppdaterar current_target till en ny position. Ska vara en ruta horisontellt eller vertikalt
      bort från nuvarande position.
     */
    virtual void select_new_target(sf::Vector2f& current_target,
                                   sf::Vector2i& current_direction) const = 0;

    sf::Vector2f current_target;
    sf::Vector2f previous_target;
    sf::Vector2i current_direction;
    Grid& grid;
    int speed;

    float time_passed {};
};

#endif
