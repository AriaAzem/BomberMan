#include "Bomb.hpp"
const sf::Time BOMB_TIME_LIMIT = sf::seconds(2);
const std::string BOMB_SPIRIT_ADDRESS = "pics/bomb.png";

void Bomb::draw_bomb(sf::RenderWindow& window, int rectangle_size)
{
    shape.setTexture(&texture);
    window.draw(shape);
}

bool Bomb::is_time_done()
{
    if(timer.getElapsedTime().asSeconds() < BOMB_TIME_LIMIT.asSeconds())
    {
        return false;
    }

    return true;
}

sf::Vector2f Bomb::get_coordinates()
{
    return coordinates;
}

Bomb::Bomb(int x, int y, sf::RenderWindow& window, int rectangle_size)
{
    coordinates = sf::Vector2f(x, y);

    sf::RectangleShape shape_set(sf::Vector2f(rectangle_size, rectangle_size));
    shape_set.setPosition(coordinates.x*rectangle_size, coordinates.y*rectangle_size);
    texture.loadFromFile(BOMB_SPIRIT_ADDRESS);
    shape_set.setTexture(&texture);
    shape = shape_set;
    window.draw(shape);
}