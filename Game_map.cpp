#include "Game_map.hpp"
#include <vector>
#include<iostream>
#include <ctime>
using namespace std;

const char WALL_SIGN = 'B';
const char DESTRUCTIBLE_WALL_SIGN = 'P';
const char PLAYER_SIGN = 'C';
const char VERTICAL_ENEMY_SIGN = 'V';
const char HORIZONAL_ENEMY_SIGN = 'H';
const char DOOR_SIGN = 'D';

const float RECTANGLE_CENTER_DISTANCE = 0.5;
const float ALLOWED_DISTANCE = 0.8;
const int MAX_BOMB_COUNT = 3;
const int POWER_UP_COUNT = 2;
const int KEY_COUNT = 3;
const int NUM_SPEED_POWER_UP = 1;
const int NUM_HEART_POWER_UP = 0;

const bool SPEED_POWER_UP = true;
const bool HEART_POWER_UP = false;
const bool DESTRUCIBLE_WALL = true;

const string EMPTY_SPACE_SPRITE_ADDRESS = "pics/grass.png";

void Game_map::generate_power_up(int x, int y, sf::RenderWindow& window, int rectangle_size)
{
    if(power_ups.size() >= POWER_UP_COUNT)
    {
        return;
    }

    if(power_ups.size() == NUM_HEART_POWER_UP)
    {
        power_ups.push_back(Power_up(x, y, window, rectangle_size, HEART_POWER_UP));
        return;
    }

    if(power_ups.size() == NUM_SPEED_POWER_UP)
    {
        power_ups.push_back(Power_up(x, y, window, rectangle_size, SPEED_POWER_UP));
        return;
    }
}

void Game_map::set_power_ups(sf::RenderWindow& window, int rectangle_size)
{
    for(int i=0; i<POWER_UP_COUNT; i++)
    {
        int marked_wall = rand() % destructible_walls_count;
        int walls_index = 0;
        for(int j=0; j<walls.size(); j++)
        {
            if(!walls[j].is_destructible())
            {
                continue;
            }

            if(walls_index == marked_wall)
            {
                generate_power_up(walls[j].get_coordinates().x, walls[j].get_coordinates().y, window, rectangle_size);
            }

            walls_index++;
        }
    }    
}
   
void Game_map::set_objects(vector<string> map_text, sf::RenderWindow &window, int rectangle_size)
{
    for (int i = 0; i < map_text.size(); i++)
    {
        for (int j = 0; j < map_text[i].size(); j++)
        {
            if(map_text[j][i] == PLAYER_SIGN)
            {
                player = Player(i, j, window, rectangle_size);
            }

            else if(map_text[j][i] == WALL_SIGN)
            {
                walls.push_back(Wall(i, j, window, rectangle_size, !DESTRUCIBLE_WALL));
            }

            else if(map_text[j][i] == DOOR_SIGN)
            {
                walls.push_back(Wall(i, j, window, rectangle_size, DESTRUCIBLE_WALL));
                destructible_walls_count++;
                doors.push_back(Door(i, j, window, rectangle_size));
            }

            else if (map_text[j][i] == DESTRUCTIBLE_WALL_SIGN)
            {
                walls.push_back(Wall(i, j, window, rectangle_size, DESTRUCIBLE_WALL));
                destructible_walls_count++;
            }

            else if (map_text[j][i] == VERTICAL_ENEMY_SIGN)
            {
                enemies.push_back(Enemy(i, j, window, rectangle_size, VERTICAL_ENEMY_SIGN));
            }

            else if (map_text[j][i] == HORIZONAL_ENEMY_SIGN)
            {
                enemies.push_back(Enemy(i, j, window, rectangle_size, HORIZONAL_ENEMY_SIGN));
            }
        }
    }
}

void Game_map::set_keys(sf::RenderWindow& window, int rectangle_size)
{
    srand((unsigned) time(0));
    for(int i=0; i<KEY_COUNT; i++)
    {
        int marked_wall = rand() % destructible_walls_count;
        int wall_index=0;
        for(int j=0; j<walls.size(); j++)
        {
            if(!walls[j].is_destructible())
            {
                continue;
            }

            if(wall_index == marked_wall)
            {
                keys.push_back(Key(walls[j].get_coordinates().x, walls[j].get_coordinates().y, window, rectangle_size));
            }

            wall_index++;
        }
    }    
} 

void Game_map::draw_empty_map(sf::RenderWindow &window, int rectangle_size)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sf::RectangleShape shape(sf::Vector2f(rectangle_size, rectangle_size));
            sf::Texture texture;
            texture.loadFromFile(EMPTY_SPACE_SPRITE_ADDRESS);
            shape.setPosition(i * rectangle_size, j * rectangle_size);
            shape.setTexture(&texture);
            window.draw(shape);
        }
    }
}

bool Game_map::is_location_blocked(float  x, float y, sf::Keyboard::Key movement_type)
{
    if ((x < 0) || (y < 0) || (x + 1) > width || (y + 1) > height)
    {
        return true;
    }

    for (int i = 0; i < walls.size(); i++)
    {
        if (walls[i].is_move_through_wall(x, y, ALLOWED_DISTANCE))
        {
            return true;
        }
    }

    return false;
}

void Game_map::handle_player_event(sf::Keyboard::Key key, int rectangle_size, sf::RenderWindow &window)
{
    if(key == sf::Keyboard::X && bombs.size()<=MAX_BOMB_COUNT)
    {
        bombs.push_back(Bomb(player.get_coordinates().x + RECTANGLE_CENTER_DISTANCE, player.get_coordinates().y + RECTANGLE_CENTER_DISTANCE, window, rectangle_size));
    }

    if(key == sf::Keyboard::Up)
    {
        if(!is_location_blocked(player.get_coordinates().x, player.get_coordinates().y - player.get_speed(), key))
        {
            player.move_player(key, rectangle_size);
        }
    }

    if (key == sf::Keyboard::Down)
    {
        if(!is_location_blocked(player.get_coordinates().x, player.get_coordinates().y + player.get_speed(), key))
        {
            player.move_player(key, rectangle_size);
        }
    }

    if (key == sf::Keyboard::Right)
    {
        if(!is_location_blocked(player.get_coordinates().x + player.get_speed(), player.get_coordinates().y, key))
        {
            player.move_player(key, rectangle_size);
        }
    }

    if(key == sf::Keyboard::Left)
    {
        if(!is_location_blocked(player.get_coordinates().x - player.get_speed(), player.get_coordinates().y, key))
        {
            player.move_player(key, rectangle_size);
        }
    }
}

void Game_map::check_enemies_hit_player()
{
    for(int i=0; i<enemies.size(); i++)
    {
        if(enemies[i].does_hit_coordinate(player.get_coordinates().x, player.get_coordinates().y, ALLOWED_DISTANCE))
        {
            player.die();
            return;
        }
    }
}

void Game_map::update_enemies_position(sf::Time time, int rectangle_size)
{
    for(int i = 0; i < enemies.size(); i++)
    {
        if(enemies[i].is_vertical())
        {
            if(!is_location_blocked(enemies[i].get_coordinates().x, (enemies[i].get_coordinates().y) + time.asSeconds() * enemies[i].get_movement_direction(), (enemies[i].get_movement_direction() > 0)? sf::Keyboard::Down : sf::Keyboard::Up))
            {
                enemies[i].enemy_move(time, rectangle_size);
            }

            else
            {
                enemies[i].change_movement_direction();
            }
        }

        else
        {
            if(!is_location_blocked(enemies[i].get_coordinates().x + time.asSeconds() * enemies[i].get_movement_direction(), enemies[i].get_coordinates().y, (enemies[i].get_movement_direction() > 0)? sf::Keyboard::Right : sf::Keyboard::Left))
            {
                enemies[i].enemy_move(time, rectangle_size);
            }

            else
            {
                enemies[i].change_movement_direction();
            }
        }
    }
}

bool Game_map::is_player_bombed(float x_bomb, float y_bomb)
{
    if(player.get_coordinates().x + RECTANGLE_CENTER_DISTANCE < x_bomb+2 && player.get_coordinates().x + RECTANGLE_CENTER_DISTANCE > x_bomb-1)
    {
        if(player.get_coordinates().y + RECTANGLE_CENTER_DISTANCE < y_bomb+1 && player.get_coordinates().y + RECTANGLE_CENTER_DISTANCE > y_bomb)
        {
            return true;
        }
    }

    if(player.get_coordinates().y + RECTANGLE_CENTER_DISTANCE < y_bomb+2 && player.get_coordinates().y + RECTANGLE_CENTER_DISTANCE > y_bomb-1)
    {
        if(player.get_coordinates().x + RECTANGLE_CENTER_DISTANCE < x_bomb+1 && player.get_coordinates().x + RECTANGLE_CENTER_DISTANCE > x_bomb)
        {
            return true;
        }
    }

    return false;
}

void Game_map::remove_destroid_objects(float x_bomb, float y_bomb)
{
    if(is_player_bombed(x_bomb, y_bomb))
    {
        player.die();
    }

    for(int i=0; i<walls.size(); i++)
    {
        if(!walls[i].is_destructible())
        {
            continue;
        }

        if(walls[i].get_coordinates() == sf::Vector2f(x_bomb-1, y_bomb) || walls[i].get_coordinates() == sf::Vector2f(x_bomb, y_bomb-1) || walls[i].get_coordinates() == sf::Vector2f(x_bomb+1, y_bomb) || walls[i].get_coordinates() == sf::Vector2f(x_bomb, y_bomb+1))
        {
            walls.erase(walls.begin()+i);
            i = 0;
        }
    }

    for(int i=0; i<enemies.size(); i++)
    {
        if(enemies[i].does_hit_coordinate(x_bomb, y_bomb, ALLOWED_DISTANCE) || enemies[i].does_hit_coordinate(x_bomb+1, y_bomb, ALLOWED_DISTANCE) || enemies[i].does_hit_coordinate(x_bomb, y_bomb+1, ALLOWED_DISTANCE) || enemies[i].does_hit_coordinate(x_bomb-1, y_bomb, ALLOWED_DISTANCE) || enemies[i].does_hit_coordinate(x_bomb, y_bomb-1, ALLOWED_DISTANCE) )
        {
            enemies.erase(enemies.begin()+i);
            i = 0;
        }
    }
}

void Game_map::update_bombs(sf::Time time)
{
    for(int i=0; i<bombs.size(); i++)
    {
        if(bombs[i].is_time_done())
        {
            remove_destroid_objects(bombs[i].get_coordinates().x, bombs[i].get_coordinates().y);
            bombs.erase(bombs.begin() + i);
        }
    }
}

void Game_map::update_power_ups()
{
    for(int i=0; i<power_ups.size(); i++)
    {
        if(!power_ups[i].is_move_through_power_up(player.get_coordinates().x, player.get_coordinates().y, ALLOWED_DISTANCE))
        {
            continue;
        }

        if(power_ups[i].is_heart_power_up())
        {
            player.add_heart();
        }

        if(power_ups[i].is_speed_power_up())
        {
            player.make_speed_twice();
        }

        power_ups.erase(power_ups.begin()+i);
        i = 0;
    }    
}

void Game_map::update_keys()
{
    for(int i=0; i<keys.size(); i++)
    {
        if(keys[i].is_move_through_key(player.get_coordinates().x, player.get_coordinates().y, ALLOWED_DISTANCE))
        {
            keys.erase(keys.begin()+i);
            i = 0;
        }
    }
}

void Game_map::update_door()
{
    for(int i=0; i<doors.size(); i++)
    {
        if(!doors[i].is_move_through_door(player.get_coordinates().x, player.get_coordinates().y, ALLOWED_DISTANCE))
        {
            continue;
        }

        if(keys.size() == 0)
        {
            doors.erase(doors.begin()+i);
        }
    }
}

void Game_map::draw_map(sf::RenderWindow &window, int rectangle_size)
{
    draw_empty_map(window, rectangle_size);

    player.draw_player(window, rectangle_size);

    for(int i=0; i<doors.size(); i++)
    {
        doors[i].draw_door(window, rectangle_size);
    }

    for(int i=0; i<keys.size(); i++)
    {
        keys[i].draw_key(window, rectangle_size);
    }

    for(int i=0; i<power_ups.size(); i++)
    {
        power_ups[i].draw_power_up(window, rectangle_size);
    }

    for(int i=0; i<bombs.size(); i++)
    {
        bombs[i].draw_bomb(window, rectangle_size);
    }

    for (int i = 0; i < walls.size(); i++)
    {
        walls[i].draw_wall(window, rectangle_size);
    }

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].draw_enemy(window);
    }
}

void Game_map::update_game_map(sf::Time time, int rectangle_size)
{
    check_enemies_hit_player();
    update_bombs(time);
    update_keys();
    update_power_ups();
    update_door();
    update_enemies_position(time, rectangle_size);  
}

Game_map::Game_map(sf::RenderWindow &window, int rectangle_size, vector<string> map_text)
{
    width = map_text.size();
    height = map_text[0].size();
    draw_empty_map(window, rectangle_size);
    set_objects(map_text, window, rectangle_size);
    set_power_ups(window, rectangle_size);
    set_keys(window, rectangle_size);
}

int Game_map::get_keys_player_got()
{
    return (KEY_COUNT - keys.size());
}

int Game_map::get_player_heart_count()
{
    return player.get_heart_count();
}

int Game_map::get_left_bombs_count()
{
    return MAX_BOMB_COUNT-bombs.size();
}

bool Game_map::is_door_picked()
{
    if(doors.size() == 0)
    {
        return true;
    }

    return false;
}