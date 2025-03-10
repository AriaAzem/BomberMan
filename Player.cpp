#include "Player.hpp"

const std::string PLAYER_DOWN_SPRITE_ADDRESS = "pics/down-stay.png";
const std::string PLAYER_UP_SPRITE_ADDRESS = "pics/up.png";
const std::string PLAYER_RIGHT_SPRITE_ADDRESS = "pics/right.png";
const std::string PLAYER_LEFT_SPRITE_ADDRESS = "pics/left.png";
const int MAX_HEART_COUNT = 3;

void Player::draw_player(sf::RenderWindow& window, int rectangle_size)
{
    shape.setTexture(&texture);
    window.draw(shape);
}

float Player::get_speed()
{
    return speed;
}

int Player::get_heart_count()
{
    return heart_count;
}

void Player::add_heart()
{
    if(heart_count < MAX_HEART_COUNT)
    {
        heart_count++;
    }
}

void Player::make_speed_twice()
{
    speed*=2;
}

sf::Vector2f Player::get_coordinates()
{
    return coordinates;
}

void Player::move_player(sf::Keyboard::Key key, int rectangle_size)
{
    switch(key)
    {
        case sf::Keyboard::Up:
            texture.loadFromFile(PLAYER_UP_SPRITE_ADDRESS);
            shape.move(0,-speed*rectangle_size);
            coordinates.y += -speed;
            break;

        case sf::Keyboard::Down:
            texture.loadFromFile(PLAYER_DOWN_SPRITE_ADDRESS);
            shape.move(0,speed*rectangle_size);
            coordinates.y += speed;          
            break;

        case sf::Keyboard::Right:
            texture.loadFromFile(PLAYER_RIGHT_SPRITE_ADDRESS);
            shape.move(speed*rectangle_size,0);
            coordinates.x += speed;          
            break;
        
        case sf::Keyboard::Left:
            texture.loadFromFile(PLAYER_LEFT_SPRITE_ADDRESS);
            shape.move(-speed*rectangle_size,0);
            coordinates.x += -speed;            
            break;

        default:
            break;
    }
}

void Player::die()
{
    coordinates.x = 0;
    coordinates.y = 0;
    shape.setPosition(0, 0);
    texture.loadFromFile(PLAYER_DOWN_SPRITE_ADDRESS);
    heart_count--;
}

Player::Player()
{

}

Player::Player(int x, int y, sf::RenderWindow& window, int rectangle_size)
{
    coordinates = sf::Vector2f(x, y);

    sf::RectangleShape shape_set(sf::Vector2f(rectangle_size, rectangle_size));
    shape_set.setPosition(coordinates.x*rectangle_size, coordinates.y*rectangle_size);
    texture.loadFromFile(PLAYER_DOWN_SPRITE_ADDRESS);
    shape_set.setTexture(&texture);
    shape = shape_set;
    window.draw(shape);
}