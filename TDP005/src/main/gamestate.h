#pragma once

#include "state.h"
#include "../world/TileMap.h"
#include "../ui/gameoverstate.h"
#include "../ui/youwin.h"

#include "../entities/player.h"
#include "../entities/enemy.h"
#include "../entities/movablething.h"
#include "../entities/swordenemy.h"
#include "../entities/arrowenemy.h"
#include "../combat/projectile.h"
#include "../entities/fountain.h"
#include "../entities/door.h"
#include "../entities/spikes.h"

/**
 * @class GameState
 * @brief Representerar huvudspelets tillstånd där spelets logik hanteras.
 * 
 * GameState ansvarar för att uppdatera spelvärlden, hantera kollisionsdetektering, 
 * fiendehantering och rendering av spelobjekt.
 */
class GameState : public State
{
public:
    /**
     * @brief Konstruktor för GameState-klassen.
     * @param window Ett pekar till spelets renderingsfönster.
     * @param states En pekar till stacken med spelets olika tillstånd.
     */
    GameState(sf::RenderWindow *window, std::stack<State*> *states, std::string currentMap);

    /**
     * @brief Destruktor för GameState-klassen.
     */
    virtual ~GameState();

    /**
     * @brief Uppdaterar GameState-logiken.
     * @param dt Delta-tiden för tidsbaserade uppdateringar.
     */
    void update(const float &dt);

    /**
     * @brief Renderar alla objekt i GameState.
     * @param target Renderingsmålet (standard är NULL).
     */
    void render(sf::RenderTarget *target = NULL);

    /**
     * @brief Kontrollerar kollisionsdetektering mellan objekt.
     */
    void checkCollisions();

    /**
     * @brief Kontrollerar kollision mellan fiender och spelaren.
     * @param enemy En pekare till en fiende.
     */
    void checkEnemyCollision(Entity& object);

    /**
     * @brief Skapar och placerar objekt på spelkartan.
     * @param x X-koordinat.
     * @param y Y-koordinat.
     * @param type Typen av objekt som ska skapas.
     */
    void spawnObjects(float x, float y, int type);

    /**
     * @brief Kontrollerar om spelaren eller fiender har dött.
     */
    void checkForDeath();

    /**
     * @brief Initialiserar spelkartan.
     */
    void initTileMap(std::string currentMap);

    /**
     * @brief Uppdaterar spelarinput.
     * @param dt Delta-tiden för input-uppdatering.
     */
    void updateInput(const float &dt);

    /**
     * @brief Initialiserar objektkartan som innehåller spelobjekt.
     */
    void initObjectMap();

    /**
     * @brief Sätter kameravy för spelet
     */
    sf::View view = window->getDefaultView();

protected:
    Player player; ///< Spelarens objekt.
    Door door; ///< Dörr-objekt i spelvärlden.
    std::vector<std::unique_ptr<Entity>> entities; ///< Vektor med unika pekare till fiender.
    std::vector<std::unique_ptr<Projectile>> arrows; ///< Vektor med unika pekare till pilar.
    void overLap(sf::FloatRect otherBounds);///< Kontrollerar om sprite hitbox overlappar med tiles.
    sf::FloatRect boundsTiles(int x, int y);

private:
    sf::RectangleShape background; ///< Bakgrundsbild för spelvärlden.
    sf::Texture bgTexture; ///< Textur som används för bakgrunden.

    /**
     * @brief Initialiserar bakgrundsbilden.
     */
    void initBackground();

    TileMap map; ///< Spelkartan.
    std::string thisMap;
    int overlapLeft;
    int overlapRight;
    int overlapTop;
    int overlapBottom;
    int minOverlapX;
    int minOverlapY;
    sf::FloatRect tileBounds;
};
