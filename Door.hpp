#ifndef DOOR_HPP
#define DOOR_HPP "DOOR_HPP"

#include <SFML/Graphics.hpp>

class Door
{
    public:
        void draw_door(sf::RenderWindow& window, int rectangle_size);
        bool is_move_through_door(float x, float y, float allowed_distance);
        Door(int x, int y, sf::RenderWindow& window, int rectangle_size);

    private:
        sf::Vector2f coordinates;
};

#endif