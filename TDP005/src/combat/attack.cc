#include "attack.h"

Attack::Attack(sf::Vector2f cord, std::string object, sf::IntRect rect)
    : MovableThing{cord, object, rect}, damage{20}
    {}

Attack::Attack()
    : damage{20}
{}