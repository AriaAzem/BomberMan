#ifndef WALL_HPP
#define WALL_HPP "WALL_HPP"

#include <SFML/Graphics.hpp>

class Wall
{
    public:
        void draw_wall(sf::RenderWindow& window, int rectangle_size);
        Wall(int x, int y, sf::RenderWindow& window, int rectangle_size, bool is_destructible);
        bool is_move_through_wall(float x, float y, float allowed_distance);
        bool is_destructible();
        sf::Vector2f get_coordinates();

    private:
        sf::Vector2f coordinates;
        bool destructible;
};

#endif