#include "Door.hpp"
#include <math.h>
const std::string DOOR_SPRITE_ADDRESS = "pics/door.png";

void Door::draw_door(sf::RenderWindow& window, int rectangle_size)
{
    sf::RectangleShape shape(sf::Vector2f(rectangle_size, rectangle_size));
    sf::Texture texture;
    texture.loadFromFile(DOOR_SPRITE_ADDRESS);   
    shape.setPosition(coordinates.x*rectangle_size, coordinates.y*rectangle_size);
    shape.setTexture(&texture);
    window.draw(shape);
}

bool Door::is_move_through_door(float x, float y, float allowed_distance)
{
    if(fabs((coordinates.x-x)*(coordinates.x-x)+(coordinates.y-y)*(coordinates.y-y)) < allowed_distance)
    {
        return true;
    }

    return false;   
}

Door::Door(int x, int y, sf::RenderWindow& window, int rectangle_size)
{
    coordinates.x = x;
    coordinates.y = y;
    draw_door(window, rectangle_size);
}