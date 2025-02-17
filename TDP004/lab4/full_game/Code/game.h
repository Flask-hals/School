#ifndef GAME_H
#define GAME_H

#include "grid.h"
#include "entity.h"
#include "pacman.h"
#include "ghost_wrapper.h"
#include "constants.h"

/*
  Spelklassen har det yttersta ansvaret för spelet. Klassen sköter huvudloopen och deligerar ansvar till andra klasser. 
 */
class Game
{
public:
    /*
      Skapa en spelinstans och alla objekt i spelvärden. De är just nu hårdkodade till specifika
      positioner. Detta borde läsas från kart-filen på ett snyggt sätt.
    */
    Game();
       
    /*
      Huvudloopen i spelet. Det är här allt utgår ifrån. Hanterar användarindata, deligerar till andra
      funktioner för att uppdatera spellogik och rendera till fönster. Gör också checkar för om spelet
      är slut.
    */
    void run();

    /*
      Uppdatera spellogik. tex flytta pacman och alla spöken.
    */
    void update();
    
    /*
      Kolla om pacman har kolliderat med någon av spökena.
    */
    bool check_collision() const;

    /*
      Rendera alla objekt i spelfönstret.
    */
    void draw();
    
    /*
      Beräkna antal poäng spelaren har samlat på sig just nu.
     */
    int get_score();

private:
    Grid grid;
    Pacman pacman;
    std::vector<Ghost_Wrapper> ghosts;
    sf::RenderWindow window;
};

#endif
