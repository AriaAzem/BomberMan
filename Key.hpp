#ifndef Key_HPP
#define Key_HPP "KEY_HPP"

#include <SFML/Graphics.hpp>

class Key
{
    public:
        void draw_key(sf::RenderWindow& window, int rectangle_size);
        bool is_move_through_key(float x, float y, float allowed_distance);
        Key(int x, int y, sf::RenderWindow& window, int rectangle_size);

    private:
        sf::Vector2f coordinates;
};

#endif