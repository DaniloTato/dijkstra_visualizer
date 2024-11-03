#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>
#include <queue>
#include <limits>
#include <sstream>
#include <optional>
#include <utility>

extern int camera_x;
extern int camera_y;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern float camera_zoom;
extern sf::Vector2i mouse_pos;

class ui{
public:
    ui(int x, int y, int width, int height);
    virtual void draw(sf::RenderWindow &window);
    void set_x( int x);
    void set_y( int y);
    int get_x();
    int get_y();
    int get_height();
    virtual void draw_rectangle(sf::RenderWindow& window);
    virtual void draw_triangle(sf::RenderWindow& window);
    virtual void draw_circle(sf::RenderWindow& window, sf::Color clr = sf::Color::Green);
    virtual sf::Vector2f return_position();
    bool check_mouse_collision();
    bool being_clicked(bool right = 0);
protected:
    int _x;
    int _y;
    int _width;
    int _height;
};

class slider: public ui{
public:
    slider(int x, int y, int width, float min_value, float max_value, int starting_value);
    void draw(sf::RenderWindow &window) override;
private:
    float _min_value;
    float _max_value;
    std::array<ui*, 4> _parts;
    ui* _knob;
    
};

class camera_sensitive: public ui{
public:
    camera_sensitive(int x, int y, int width, int height, float paralax = 1);
    void draw_rectangle(sf::RenderWindow& window) override;
    void draw_circle(sf::RenderWindow& window, sf::Color clr = sf::Color::Green) override;
    virtual sf::Vector2f return_position() override;
protected:
    float _paralax;
};

class node: public camera_sensitive{
public:
    node(int x, int y, int longitude, int latitude, int radius, std::string name = "#default_node", float paralax = 1);
    std::vector<std::pair<int, int>> _paths;
    bool _has_temp_vector = 0;
    std::string _name;
    std::string _original_name;
    sf::Vector2f get_geo_chords();
    void update_name(std::vector<node*>& node_vector);
    void draw_circle(sf::RenderWindow& window, sf::Color clr = sf::Color::Green) override;
protected:
    int _longitude = 0;
    int _latitude = 0;
    sf::Font _font;
    sf::Text _name_text;
};

#include "../src/functions.cpp"

#endif