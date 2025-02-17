
#include <SFML/Graphics.hpp>
#include <iostream>

#include "game.h" 

using namespace std;

int main()
{
    cout << "Välkommen till Pacman\nTryck 'Enter' för att starta";
    cin.get();

    Game game {};
    game.run();

    cout << "Du fick " << game.get_score() << " poäng" << std::endl;
    cout << "Tryck 'Enter' för att avsluta" << std::endl;
    cin.get();
}
