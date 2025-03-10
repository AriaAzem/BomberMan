#ifndef BOMB_HPP
#define BOMB_HPP "BOMB_HPP"

#include <SFML/Graphics.hpp>

class Bomb
{
    public:
        Bomb(int x, int y, sf::RenderWindow& window, int rectangle_size);
        bool is_time_done();
        sf::Vector2f get_coordinates();
        void draw_bomb(sf::RenderWindow& window, int rectangle_size);

    private:
        sf::Clock timer;
        sf::Vector2f coordinates;
        sf::RectangleShape shape;
        sf::Texture texture;
};

#endif