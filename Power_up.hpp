#ifndef POWER_UP_HPP
#define POWER_UP_HPP "POWER_UP"

#include <SFML/Graphics.hpp>
 
class Power_up
{
    public:
        void draw_power_up(sf::RenderWindow& window, int rectangle_size);
        bool is_move_through_power_up(float x, float y, float allowed_distance);
        bool is_heart_power_up();
        bool is_speed_power_up();
        Power_up(int x, int y, sf::RenderWindow& window, int rectangle_size, bool is_speed_up);


    private:
        sf::Vector2f coordinates;
        bool speed_up_type;
};

#endif