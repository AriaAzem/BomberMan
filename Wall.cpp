#include "Wall.hpp"
#include <iostream>
#include <cstdlib>
#include <math.h>

const std::string DESTRUCTIBLE_WALL_SPRITE_ADDRESS = "pics/wall-1.png";
const std::string WALL_SPRITE_ADDRESS = "pics/wall-2.png";

void Wall::draw_wall(sf::RenderWindow& window, int rectangle_size)
{
    sf::RectangleShape shape(sf::Vector2f(rectangle_size, rectangle_size));
    sf::Texture texture;

    if(destructible)
    {
        texture.loadFromFile(DESTRUCTIBLE_WALL_SPRITE_ADDRESS);
    }

    else
    {
        texture.loadFromFile(WALL_SPRITE_ADDRESS);
    }
        
    shape.setPosition(coordinates.x*rectangle_size, coordinates.y*rectangle_size);
    shape.setTexture(&texture);
    window.draw(shape);
}

bool Wall::is_move_through_wall(float x, float y, float allowed_distance)
{
    if(fabs((coordinates.x-x)*(coordinates.x-x)+(coordinates.y-y)*(coordinates.y-y)) < allowed_distance)
    {
        return true;
    }

    return false;
}

bool Wall::is_destructible()
{
    return destructible;
}

sf::Vector2f Wall::get_coordinates()
{
    return coordinates;
}

Wall::Wall(int x, int y, sf::RenderWindow& window, int rectangle_size, bool is_destructible)
{
    destructible = is_destructible;
    coordinates.x = x;
    coordinates.y = y;
    draw_wall(window, rectangle_size);
}

