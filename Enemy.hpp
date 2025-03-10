#ifndef ENEMY_HPP
#define ENEMY_HPP "ENEMY_HPP"

#include <SFML/Graphics.hpp>

const int DOWN_OR_RIGHT_DIRECTION = 1;
const int UP_OR_LEFT_DIRECTION = -1;

class Enemy
{
    public:
        void change_movement_direction();
        void draw_enemy(sf::RenderWindow& window);
        void enemy_move(sf::Time time, int rectangle_size);
        bool does_hit_coordinate(float x, float y, float allowed_distance);
        int get_movement_direction();
        sf::Vector2f get_coordinates();
        bool is_vertical();
        Enemy(int x, int y, sf::RenderWindow& window, int rectangle_size, char vertical_or_horizonal);

    private:
        sf::Vector2f coordinates;
        sf::RectangleShape shape;
        sf::Texture texture;
        char vertical_or_horizonal;
        void vertical_move(sf::Time time, int rectangle_size);
        void horizonal_move(sf::Time time, int rectangle_size);
        int movement_direction = (rand()%2 == 1) ? DOWN_OR_RIGHT_DIRECTION : UP_OR_LEFT_DIRECTION;
};

#endif