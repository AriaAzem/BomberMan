#include "Key.hpp"
#include <math.h>
const std::string KEY_SPRITE_ADDRESS = "pics/key.png";

void Key::draw_key(sf::RenderWindow& window, int rectangle_size)
{
    sf::RectangleShape shape(sf::Vector2f(rectangle_size, rectangle_size));
    sf::Texture texture;
    texture.loadFromFile(KEY_SPRITE_ADDRESS);   
    shape.setPosition(coordinates.x*rectangle_size, coordinates.y*rectangle_size);
    shape.setTexture(&texture);
    window.draw(shape);
}

bool Key::is_move_through_key(float x, float y, float allowed_distance)
{
    if(fabs((coordinates.x-x)*(coordinates.x-x)+(coordinates.y-y)*(coordinates.y-y)) < allowed_distance)
    {
        return true;
    }

    return false;   
}

Key::Key(int x, int y, sf::RenderWindow& window, int rectangle_size)
{
    coordinates.x = x;
    coordinates.y = y;
    draw_key(window, rectangle_size);
}