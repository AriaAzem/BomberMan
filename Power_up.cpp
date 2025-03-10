#include "Power_up.hpp"
#include <math.h>
const std::string SPEED_SPRITE_ADDRESS = "pics/lightning.png";
const std::string HEART_SPRIET_ADDRESS = "pics/heart.png";

void Power_up::draw_power_up(sf::RenderWindow& window, int rectangle_size)
{
    sf::RectangleShape shape(sf::Vector2f(rectangle_size, rectangle_size));
    sf::Texture texture;

    if(speed_up_type)
    {
        texture.loadFromFile(SPEED_SPRITE_ADDRESS);
    }

    else
    {
        texture.loadFromFile(HEART_SPRIET_ADDRESS);
    }
        
    shape.setPosition(coordinates.x*rectangle_size, coordinates.y*rectangle_size);
    shape.setTexture(&texture);
    window.draw(shape);
}

bool Power_up::is_heart_power_up()
{
    return !speed_up_type;
}

bool Power_up::is_speed_power_up()
{
    return speed_up_type;
}

bool Power_up::is_move_through_power_up(float x, float y, float allowed_distance)
{
    if(fabs((coordinates.x-x)*(coordinates.x-x)+(coordinates.y-y)*(coordinates.y-y)) < allowed_distance)
    {
        return true;
    }

    return false;   
}

Power_up::Power_up(int x, int y, sf::RenderWindow& window, int rectangle_size, bool is_speed_up)
{
    coordinates.x = x;
    coordinates.y = y;
    speed_up_type = is_speed_up;
    draw_power_up(window, rectangle_size);
}