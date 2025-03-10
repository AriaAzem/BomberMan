#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "Game_map.hpp"
using namespace std;

const int LINE_OF_GAME_TIME = 0;
const sf::Time UPDATE_TIME = sf::seconds(0.05); 

const sf::Vector2f TIMER_POSITION = sf::Vector2f(515, 20);
const sf::Color TIMER_FONT_COLOR = sf::Color::Red;
const int TIMER_FONT_SIZE = 30;
const string TIME_MESSAGE = "This game will end in:";
const string TIMER_FONT = "BADABB__.TTF";

const sf::Vector2f PLAYER_INFO_POSITION = sf::Vector2f(515, 110);
const sf::Color PLAYER_FONT_COLOR = sf::Color::White;
const int PLAYER_INFO_FONT_SIZE = 30;
const string PLAYER_INFO_FONT = "BADABB__.TTF";
const string HEART_MESSAGE = " HEART : ";
const string KEYS_MESSAGE = " KEYS : ";
const string BOMBS_MESSAGE = " BOMB LEFT :";

const sf::Vector2f RESULT_POSITION = sf::Vector2f(530, 300);
const string WIN_MESSAGE = "YOU WIN!!!";
const string LOSE_MESSAGE = "GAME OVER!";
const sf::Color RESULT_FONT_COLOR = sf::Color::Green;
const int RESULT_FONT_SIZE = 40;
const string RESULT_FONT = "BADABB__.TTF";


const int RECTANGLE_SIZE = 50;
const int WINDOW_WIDTH = 750;
const int WINDOW_HEIGHT = 500;

const string MAP_TEXT_ADDRESS = "map.txt";
const string GAME_NAME = "BOMBER MAN";

void draw_timer(sf::RenderWindow& window, sf::Clock& clock, int game_time)
{
    sf::Font font;
    font.loadFromFile(TIMER_FONT);
    sf::Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(TIMER_FONT_SIZE);
    timerText.setFillColor(TIMER_FONT_COLOR);
    timerText.setPosition(TIMER_POSITION);

    sf::Time elapsed = clock.getElapsedTime();
    sf::Time remaining = sf::Time(sf::seconds(game_time)) - elapsed;
    if (remaining.asSeconds() < 0)
    {
        remaining = sf::seconds(0);
    }

    stringstream message;
    message << TIME_MESSAGE << endl << static_cast<int>(remaining.asSeconds());

    timerText.setString(message.str());
    window.draw(timerText);
}

void print_player_info(Game_map& game_map, sf::RenderWindow& window)
{
    sf::Font font;
    font.loadFromFile(PLAYER_INFO_FONT);
    sf::Text player_info;
    player_info.setFont(font);
    player_info.setCharacterSize(PLAYER_INFO_FONT_SIZE);
    player_info.setFillColor(PLAYER_FONT_COLOR);
    player_info.setPosition(PLAYER_INFO_POSITION);

    stringstream message;
    message << HEART_MESSAGE << game_map.get_player_heart_count() << endl
    << endl << BOMBS_MESSAGE << game_map.get_left_bombs_count() << endl
    << endl << KEYS_MESSAGE << game_map.get_keys_player_got() << endl;

    player_info.setString(message.str());
    window.draw(player_info);
}

vector<string> read_map_from_file(string fileName, int& game_time)
{
    fstream fin;
    fin.open(fileName, ios::in);

    vector<string> result;
    int line_count = 0;
    string line;

	while(getline(fin, line))
	{
        if(line_count == LINE_OF_GAME_TIME)
        {
            game_time = stoi(line);
        }

        else
        {
            result.push_back(line);
        }

        line_count++;
    }
    
    return result;
}

void handle_events(Game_map& game_map, sf::RenderWindow& window)
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                game_map.handle_player_event(event.key.code, RECTANGLE_SIZE, window);
                    break;
                    
            default:
                break;
        }
    }
}

bool finish_game(Game_map& game_map, sf::RenderWindow& window, sf::Clock clock, int game_time)
{
    sf::Font font;
    font.loadFromFile(RESULT_FONT);
    sf::Text game_result;
    game_result.setFont(font);
    game_result.setCharacterSize(RESULT_FONT_SIZE);
    game_result.setFillColor(RESULT_FONT_COLOR);
    game_result.setPosition(RESULT_POSITION);

    stringstream message;
    if(game_map.is_door_picked())
    {
        message << WIN_MESSAGE << endl;  
    }

    else if(clock.getElapsedTime().asSeconds() >= game_time || game_map.get_player_heart_count() == 0)
    {
        message << LOSE_MESSAGE << endl;    
    }

    else
    {
        return false;
    }

    game_result.setString(message.str());
    window.draw(game_result);
    return true;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
    sf::Clock clock;
    int game_time;
    Game_map game_map(window, RECTANGLE_SIZE, read_map_from_file(MAP_TEXT_ADDRESS, game_time));
    
    while(window.isOpen())
    {
        window.clear();

        if(!finish_game(game_map,window, clock, game_time))
        {
            handle_events(game_map, window);
            draw_timer(window, clock, game_time);
        }
            
        game_map.update_game_map(UPDATE_TIME, RECTANGLE_SIZE);
        game_map.draw_map(window, RECTANGLE_SIZE);
        print_player_info(game_map, window);
        window.display();
    }

    return 0;
}