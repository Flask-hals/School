#ifndef PACMAN_H
#define PACMAN_H

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "grid.h"

/*
  Pacmanklassen representerar spelarefiguren i spelet. Den innehåller funktionallitet för att flytta och rendera spelarefiguren. 

  Är en specialicering av basklassen Entity.
 */
class Pacman : public Entity
{
public:
    Pacman(sf::Vector2f const& start_position, Grid& grid);

    /*
      Uppdatera pacmans position och riktning.
     */
    void update() override;

    /*
      Hämta ut olika egenskaper från pacman.
     */
    unsigned get_score() const { return score; };
    Point get_position()  const;
    Point get_direction() const;

protected:

    /*
      Använder användainmatning för att beräkna vilken nästa ruta spelare ska röra sig till är.
     */
    void select_new_target(sf::Vector2f& current_target,
                           sf::Vector2i& current_direction) const override;
    
private:

    /*
      Kollar vilka knappar som är nedtryckta och uppdaterar variabeln next_direction baserat på det.

      Ändra i denna om du vill ha andra knappar som styr spelaren.
     */
    void handle_input();

    sf::Vector2i next_direction;
    unsigned score;
};

#endif
