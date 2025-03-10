#ifndef PLAYER_HPP
#define PLAYER_HPP "PLAYER_HPP"

#include <SFML/Graphics.hpp>
const float INIT_SPEED = 0.1;
const int INIT_HEART_COUNT = 2;

class Player
{
    public:
        void draw_player(sf::RenderWindow& window, int rectangle_size);
        void move_player(sf::Keyboard::Key key, int rectangle_size);
        void die();
        float get_speed();
        int get_heart_count();
        void make_speed_twice();
        void add_heart();
        sf::Vector2f get_coordinates();
        Player();
        Player(int x, int y, sf::RenderWindow& window, int rectangle_size);


    private:
        sf::Vector2f coordinates;
        sf::RectangleShape shape;
        sf::Texture texture;
        int heart_count = INIT_HEART_COUNT;
        float speed = INIT_SPEED;
};

#endif