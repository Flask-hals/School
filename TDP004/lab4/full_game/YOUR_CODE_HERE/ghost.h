#ifndef GHOST_H
#define GHOST_H
#include "given.h"

// Vi har valt att lägga alla spöken i samma fil eftersom att varje klass har få rader kod, vilket gör det mer lättläst med en fil.

class Ghost
{
public:
  Ghost(Pacman const& pacman, Point start, Point scatter);
    virtual ~Ghost() = default;

    virtual Point get_chase_point() = 0;
    virtual Point get_scatter_point();
    std::string get_color() const;
    virtual void set_position(Point const& p);
    Point get_position() const;

protected:
    Pacman const& pacman;
    Point pos {};
    Point start;
    Point scatter;
    std::string color{};
};

class Blinky : public Ghost
{
public:
  Blinky(Pacman const& pacman, Point start, Point scatter);

    bool is_angry();
    void set_angry(bool);

    Point get_chase_point();
    Point get_scatter_point() override;

private:
    bool anger {false};
    std::string color{"red"};

};

class Pinky : public Ghost
{
public:
  Pinky(Pacman const& pacman, Point start, Point scatter);

    Point get_chase_point();

private:
    std::string color{"pink"};

};

class Clyde : public Ghost
{
public:
  Clyde(Pacman const& pacman, Point start, Point scatter, int n);
    
    Point get_chase_point();

private:
    int n {};
    std::string color{"orange"};

};

#endif
