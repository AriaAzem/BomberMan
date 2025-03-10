#include "Enemy.hpp"
#include <math.h>
const std::string ENEMY_SPRITE_ADDRESS = "pics/enemy.png";
const char VERTICAL_SIGN = 'V';
const char HORIZONAL_SIGN = 'H';

void Enemy::change_movement_direction()
{
    movement_direction *= -1;
}

void Enemy::vertical_move(sf::Time time, int rectangle_size)
{
    shape.move(0, (time.asSeconds()*movement_direction*rectangle_size)); 
    coordinates.y += time.asSeconds()*movement_direction;   
}

void Enemy::horizonal_move(sf::Time time, int rectangle_size)
{
    shape.move((time.asSeconds()*movement_direction*rectangle_size), 0); 
    coordinates.x += time.asSeconds()*movement_direction;       
}

void Enemy::enemy_move(sf::Time time, int rectangle_size)
{
    if(vertical_or_horizonal == HORIZONAL_SIGN)
    {
        horizonal_move(time, rectangle_size);
        return;
    }

    else if(vertical_or_horizonal == VERTICAL_SIGN)
    {
        vertical_move(time, rectangle_size);
        return;
    }

    return;
}

bool Enemy::does_hit_coordinate(float x, float y, float allowed_distance)
{
    if(fabs((coordinates.x-x)*(coordinates.x-x)+(coordinates.y-y)*(coordinates.y-y)) < allowed_distance)
    {
        return true;
    }

    return false;
}

void Enemy::draw_enemy(sf::RenderWindow& window)
{
    shape.setTexture(&texture);
    window.draw(shape);
}

bool Enemy::is_vertical()
{
    if(vertical_or_horizonal == VERTICAL_SIGN)
    {
        return true;
    }

    return false;
}

sf::Vector2f Enemy::get_coordinates()
{
    return coordinates;
}

int Enemy::get_movement_direction()
{
    return movement_direction;
}

Enemy::Enemy(int x, int y, sf::RenderWindow &window, int rectangle_size, char movement)
{
    coordinates = sf::Vector2f(x, y);
    vertical_or_horizonal = movement;

    sf::RectangleShape shape_set(sf::Vector2f(rectangle_size, rectangle_size));
    texture.loadFromFile(ENEMY_SPRITE_ADDRESS);
    shape_set.setPosition(coordinates.x*rectangle_size, coordinates.y*rectangle_size);
    shape_set.setTexture(&texture);

    shape = shape_set;
    window.draw(shape);
}