#include "../include/header.hpp"

node::node(int x, int y, int longitude, int latitude, int radius, std::string name, float paralax):
_original_name(name), _name(name), _longitude(longitude), _latitude(latitude), camera_sensitive(x,y,radius,radius,paralax){
    _font.loadFromFile("arial.ttf");
    _name_text.setFont(_font);
    _name_text.setCharacterSize(10);
    _name_text.setFillColor(sf::Color::Black);
    _name_text.setString(_name);
}

sf::Vector2f node::get_geo_chords(){
    return sf::Vector2f(_longitude, _latitude);
}

void node::update_name(std::vector<node*>& node_vector){
    std::string temp_name = _original_name;
    int times_found = 0;
    
    while(found_in_vector(node_vector, temp_name, this)){
        times_found++;
        temp_name = _original_name + std::to_string(times_found);
    }

    _name = temp_name;

    _name_text.setString(_name);
}

void node::draw_circle(sf::RenderWindow& window, sf::Color clr){
    camera_sensitive::draw_circle(window, clr);

    sf::Vector2f my_pos = return_position();
    _name_text.setPosition(my_pos.x, my_pos.y);
    window.draw(_name_text);

}