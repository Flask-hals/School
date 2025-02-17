#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>

/*
  Datatyp för att representera en rad i rutnätet som är kartan.
 */
using Row = std::vector<char>;
std::istream& operator>>(std::istream& is, Row& row);

/*
  Hjälpfunktioner för att konvertera mellan två olika coordinatsystem.

  'grid' är ett coordinatsystem där varje ruta på spelplanen är en coordinat.
  'world' är ett coordinatsystem där varje pixel på skärmen är en coordinat.
 */
sf::Vector2i to_grid_pos(sf::Vector2f const& pos);
sf::Vector2f to_world_pos(sf::Vector2i const& pos);

/*
  Klass som representerar hela kartan. Dvs håller koll på alla positioner för väggar och mat på
  kartan.
 */
class Grid
{
public:

    Grid(std::string const& map_file);

    /*
      Rendera alla väggar och all mat.
    */
    void draw(sf::RenderWindow& window) const;

    /*
      Ger sant om det är en vägg på given position. Notera att positionen måste anges i
      'grid'-systemet.
    */
    bool wall_at(sf::Vector2i const& grid_pos) const;

    /*
      Ger sant om det var en mat på given position. Plockar då också bort maten. Notera att
      positionen måste anges i 'grid'-systemet.

      Om det inte var en mat på positionen returneras 'false' och inget mer händer. 
    */
    bool eat_food(sf::Vector2i const& grid_pos);

    int food_count() const;

private:
    std::vector<Row> rows {};
};

#endif
