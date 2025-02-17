#include "ghost.h"
#include <cmath>

Ghost::Ghost(Pacman const& pacman, Point start, Point scatter, std::string const& color)
    : pacman{pacman}, start{start}, scatter{scatter}, color{color}
{}

std::string Ghost::get_color() const
{
    return color;
}

Point Ghost::get_position() const
{
    return pos;
}

Point Ghost::get_scatter_point()
{
    return scatter;
}

void Ghost::set_position(Point const &p)
{
    if (p.x > WIDTH or p.x < 0 or p.y > HEIGHT or p.y < 0)
    {
        throw std::runtime_error("position outside valid range");
    }
    pos = p;
}

//-------------------------------------------

Blinky::Blinky(Pacman const& pacman, Point start, Point scatter, std::string const& color)
    : Ghost(pacman, start, scatter, color)
{}

Point Blinky::get_scatter_point()
{
    if (this->is_angry())
    {
        return Point{pacman.get_position().x, pacman.get_position().y};
    }
    return scatter;
}

Point Blinky::get_chase_point()
{
    return Point{pacman.get_position().x, pacman.get_position().y};
}

bool Blinky::is_angry()
{
    return anger;
}

void Blinky::set_angry(bool angry)
{
    anger = angry;
}

//-------------------------------------------

Pinky::Pinky(Pacman const& pacman, Point start, Point scatter, std::string const& color)
    : Ghost(pacman, start, scatter, color)
{}

Point Pinky::get_chase_point()
{
    if (pacman.get_direction().x == 1)
    {
        return Point{pacman.get_position().x + 2, pacman.get_position().y};
    }
    else if (pacman.get_direction().x == -1)
    {
        return Point{pacman.get_position().x - 2, pacman.get_position().y};
    }
    else if (pacman.get_direction().y == 1)
    {
        return Point{pacman.get_position().x, pacman.get_position().y + 2};
    }
    else
    {
        return Point{pacman.get_position().x, pacman.get_position().y - 2};
    }
}

//-------------------------------------------

Clyde::Clyde(Pacman const& pacman, Point start, Point scatter, int n, std::string const& color)
    : Ghost(pacman, start, scatter, color), n{n}
{}

Point Clyde::get_chase_point()
{
    if (std::sqrt(std::pow((pacman.get_position().x - this->get_position().x), 2) +
                std::pow((this->get_position().y - pacman.get_position().y), 2)) <= n)
    {
        return Point{pacman.get_position().x, pacman.get_position().y};
    }
    else
    {
        return this->get_scatter_point();
    }
}