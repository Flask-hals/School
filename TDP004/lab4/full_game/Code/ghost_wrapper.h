#ifndef GHOST_WRAPPER_H
#define GHOST_WRAPPER_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "entity.h"
#include "grid.h"
#include "YOUR_CODE_HERE/ghost.h"

/*
  En klass som äger ett objekt av den studentskapade datatypen "Ghost". Se detta som en klass som
  lägger till grafikelement och sökalgoritm till klasserna som studenten skapat.

 */
class Ghost_Wrapper : public Entity
{
public:
    Ghost_Wrapper(sf::Vector2f const& start_position, Grid& grid, Ghost* ghost);
    
    /*
      Utökar Entitys update med funktionallitet för att byta mellan chase och scatter.

      Anropar sedan Entitys update. Kolla där för detaljer.
     */
    void update() override;

protected:

    /*
      Väljer en ny punkt för spöket att gå till. Detta görs när spöket har nått sitt förra mål.

      Notera att detta inte är samma sak som det studenten ska implementera. Detta är ruta för ruta
      och använder sig av studentkod, men de är inte samma.
     */
    void select_new_target(sf::Vector2f& current_target,
                           sf::Vector2i& current_direction) const override;

private:

    /*
      Konverterar den färg-strängen som spöket sparar till en faktiskt sfml-färg.

      Följ mönstret för att lägga till fler färger.
     */
    sf::Color get_sfml_color(Ghost* ghost) const;

    std::unique_ptr<Ghost> ghost;
    bool chase_mode {true};
};

#endif
