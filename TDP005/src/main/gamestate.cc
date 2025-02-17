#include "gamestate.h"

GameState::GameState(sf::RenderWindow *window, std::stack<State *> *states, std::string currentMap)
    : State(window, states), player{sf::Vector2f(500, 300), "player", sf::IntRect(0, 0, 64, 90)}, thisMap{currentMap}, overlapLeft{}, overlapRight{}, overlapTop{}, overlapBottom{}, minOverlapX{}, minOverlapY{}, tileBounds{}
{
    initTileMap(currentMap);
    initBackground();
    initObjectMap();
}

GameState::~GameState()
{
}

void GameState::initTileMap(std::string currentMap)
{
    map.loadfile(currentMap);
}

void GameState::update(const float &dt)
{
    updateInput(dt);
    player.update(dt, player);

    for (size_t i = 0; i < entities.size();)
    {
        auto &object = entities[i];

        player.update(dt, *object);
        object->update(dt, player);

        if (!object->checkActive())
        {
            entities.erase(entities.begin() + i);
        }
        else
        {
            ++i;
            if (object->shootProjectile())
            {
                arrows.emplace_back(std::make_unique<Projectile>(sf::Vector2f(object->getPosition()), "projectile", sf::IntRect(70, 0, 80, 85)));
            }
            if (Enemy *enemy = dynamic_cast<Enemy *>(object.get()))
            {
                checkEnemyCollision(*enemy);
            }
        }
    }
    entities.insert(
    entities.end(),
    std::make_move_iterator(arrows.begin()),
    std::make_move_iterator(arrows.end()));

    arrows.clear();

    sf::FloatRect door_hbox{door.getGlobalBounds()};
    if (player.getGlobalBounds().intersects(door_hbox))
    {
        if (thisMap == "src/levels/map2.txt")
        {
            states->pop();
            states->push(new YouWin(window, states));
        }
        else
        {
            states->pop();
            states->push(new GameState(window, states, "src/levels/map2.txt"));
        }
    }
    checkCollisions();
}

void GameState::render(sf::RenderTarget *target)
{
    if (!target)
        target = window;

    view.setCenter(player.getPosition().x, 332);
    window->setView(view);

    window->draw(background);

    map.render(*target);

    door.render(target);

    player.render(target);

    for (auto &object : entities)
    {
        if (object->checkActive())
        {
            object->render(target);
        }
    }
}

void GameState::checkForDeath()
{
    if (!player.checkActive())
    {
        states->pop();
        states->push(new GameOver(window, states));
    }
}

void GameState::checkCollisions()
{
    for (size_t y = 0; y < map.getRowCount(); ++y)
    {
        for (size_t x = 0; x < map.getColumnCount(y); ++x)
        {
            const auto &[tilePos, collidable] = map.getTile(x, y);

            if (collidable)
            {
                // Calculate the tile bounds (position and size)
                tileBounds = boundsTiles(x, y);

                if (tileBounds.intersects(player.getGlobalBounds()))
                {
                    sf::FloatRect playerBounds = player.getGlobalBounds();
                    overLap(playerBounds);

                    if (minOverlapX < minOverlapY)
                    {
                        // Horizontal collision
                        if (overlapLeft < overlapRight)
                        {
                            // Colliding from the left
                            player.setPosition(tileBounds.left - 32, player.getPosition().y); //-32
                            // player.changeVelocity(0, player.getVelocity().y);                 // Stop horizontal movement
                        }
                        else
                        {
                            // Colliding from the right
                            player.setPosition(tileBounds.left + 64, player.getPosition().y); // +64
                            // player.changeVelocity(0, player.getVelocity().y);                 // Stop horizontal movement
                        }
                    }
                    else
                    {
                        // Vertical collision
                        if (overlapTop < overlapBottom)
                        {
                            // Colliding from the top
                            player.setPosition(player.getPosition().x, tileBounds.top - 45); // -45
                            player.changeVelocity(player.getVelocity().x, 0);                // Stop vertical movement
                            player.changeJump();
                        }
                        else
                        {
                            // Colliding from the bottom
                            player.setPosition(player.getPosition().x, tileBounds.top + 90); // +90
                            player.changeVelocity(player.getVelocity().x, 0);                // Stop vertical movement
                        }
                    }
                }
            }
        }
    }
}

void GameState::spawnObjects(float x, float y, int type)
{
    if (type == 1)
        entities.push_back(std::make_unique<SwordEnemy>(sf::Vector2f(x, y), "swordenemy", sf::IntRect(0, 180, 64, 90)));
    else if (type == 2)
        entities.push_back(std::make_unique<ArrowEnemy>(sf::Vector2f(x, y), "arrowenemy", sf::IntRect(0, 0, 64, 90)));
    else if (type == 3)
        entities.push_back(std::make_unique<Fountain>(sf::Vector2f(x, y), "fountain", sf::IntRect(0, 0, 128, 128)));
    else if (type == 4)
        door = Door(sf::Vector2f(x, y), "door", sf::IntRect(0, 0, 172, 256));
    else if (type == 5)
        entities.push_back(std::make_unique<Spikes>(sf::Vector2f(x, y + 17), "spikes", sf::IntRect(0, 0, 32, 32)));
}

void GameState::checkEnemyCollision(Entity &object)
{
    bool isGrounded = false;
    if (Enemy *enemy = dynamic_cast<Enemy *>(&object))
    {
        for (size_t y = 0; y < map.getRowCount(); ++y)
        {
            for (size_t x = 0; x < map.getColumnCount(y); ++x)
            {
                const auto &[tilePos, collidable] = map.getTile(x, y);

                if (collidable)
                {
                    // Calculate the tile bounds (position and size)
                    tileBounds = boundsTiles(x, y);

                    if (boundsTiles(x, y).intersects(object.getGlobalBounds()))
                    {
                        sf::FloatRect enemyBounds = object.getGlobalBounds();
                        overLap(enemyBounds);
                        if (minOverlapX < minOverlapY)
                        {
                            // Horizontal collision
                            if (overlapLeft < overlapRight)
                            {
                                enemy->handleMapCollision(tileBounds.left - tileBounds.width, enemy->getPosition().y);
                            }
                            else
                            {
                                enemy->handleMapCollision(tileBounds.left + tileBounds.width, enemy->getPosition().y);
                            }
                        }
                        else
                        {
                            // Vertical collision
                            if (overlapTop < overlapBottom)
                            {
                                isGrounded = true;
                                enemy->handleMapCollision(enemy->getPosition().x, tileBounds.top - tileBounds.height - 12.5);
                            }
                            else
                            {
                                enemy->handleMapCollision(enemy->getPosition().x, tileBounds.top + tileBounds.height);
                            }
                        }
                    }
                }
            }
        }
        enemy->setGravity(!isGrounded);
    }
};

void GameState::initBackground()
{
    background.setSize(sf::Vector2f(4153, 445));

    if (!bgTexture.loadFromFile("src/assets/castle.png"))
    {
        throw "ERROR: castle.png could not load in";
    }
    background.setTexture(&bgTexture);
}

void GameState::updateInput(const float &dt)
{
    checkForDeath();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        endState();
    }
}

void GameState::initObjectMap()
{
    for (size_t y = 0; y < map.getRowCount(); ++y)
    {
        for (size_t x = 0; x < map.getColumnCount(y); ++x)
        {
            if (map.getTile(x, y).first.x == 1)
            {
                spawnObjects(x * 32, y * 32, 1);
            }
            if (map.getTile(x, y).first.x == 2)
            {
                spawnObjects(x * 32, y * 32, 2);
            }
            if (map.getTile(x, y).first.y == 3)
            {
                spawnObjects(x * 32, y * 32, 3);
            }
            if (map.getTile(x, y).first.x == 3)
            {
                spawnObjects(x * 32, y * 32, 4);
            }
            if (map.getTile(x, y).first.x == 4)
            {
                spawnObjects(x * 32, y * 32, 5);
            }
        }
    }
}

void GameState::overLap(sf::FloatRect otherBounds)
{
    overlapLeft = otherBounds.left + otherBounds.width - tileBounds.left;
    overlapRight = tileBounds.left + tileBounds.width - otherBounds.left;
    overlapTop = otherBounds.top + otherBounds.height - tileBounds.top;
    overlapBottom = tileBounds.top + tileBounds.height - otherBounds.top;

    // Find the minimum overlap direction
    minOverlapX = std::min(overlapLeft, overlapRight);
    minOverlapY = std::min(overlapTop, overlapBottom);
}

sf::FloatRect GameState::boundsTiles(int x, int y)
{
    sf::FloatRect tiles(static_cast<float>(x * 32), static_cast<float>(y * 32), 32, 32);
    return tiles;
}