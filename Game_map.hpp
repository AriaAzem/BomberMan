#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP "GAME_MAP_HPP"

#include <SFML/Graphics.hpp>
#include "Wall.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Bomb.hpp"
#include "Power_up.hpp"
#include "Key.hpp"
#include "Door.hpp"

using namespace std;

class Game_map
{
    public:
        void handle_player_event(sf::Keyboard::Key key, int rectangle_size, sf::RenderWindow& window);      
        void draw_map(sf::RenderWindow& window, int rectangle_size);
        void update_game_map(sf::Time time, int rectangle_size);
        int get_keys_player_got();
        int get_player_heart_count();
        int get_left_bombs_count();
        bool is_door_picked();
        Game_map(sf::RenderWindow& window, int rectangle_size, vector<string> map_text);

    private:
        int destructible_walls_count = 0;
        Player player;
        vector<Wall> walls;
        vector<Enemy> enemies;
        vector<Bomb> bombs;
        vector<Power_up> power_ups;
        vector<Key> keys;
        vector<Door> doors;
        int width;
        int height;
        void set_objects(vector<string> map_text, sf::RenderWindow& window, int rectangle_size); 
        bool is_location_blocked(float x, float y, sf::Keyboard::Key movement_type);
        void draw_empty_map(sf::RenderWindow& window, int rectangle_size);
        void update_power_ups();
        void update_keys();
        void update_door();
        void update_enemies_position(sf::Time time, int rectangle_size);
        void update_bombs(sf::Time time);
        bool is_player_bombed(float x_bomb, float y_bomb); 
        void remove_destroid_objects(float x_bomb, float y_bomb);
        void generate_power_up(int x, int y, sf::RenderWindow& window, int rectangle_size);
        void set_power_ups(sf::RenderWindow& window, int rectangle_size);
        void set_keys(sf::RenderWindow& window, int rectangle_size);
        void check_enemies_hit_player();              
};

#endif