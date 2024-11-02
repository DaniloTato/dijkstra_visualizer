#include "../include/header.hpp"

slider::slider(int x, int y, int width, float min_value, float max_value, int starting_value):
ui(x,y,width,10){
    _parts[0] = new ui(0,0,200,_height);
    _parts[1] = new ui(0,0,_height,_height);
    _parts[2] = new ui(0,0,_height,_height);
    _knob = new ui(x,y,_height,_height);
}

void slider::draw(sf::RenderWindow &window){

    //check_mouse_collision();
    _parts[0]->set_x(_x);
    _parts[0]->set_y(_y);

    _parts[1]->set_x(_x);
    _parts[1]->set_y(_y - _parts[1] -> get_height() * 0.5);

    _parts[1]->set_x(_x);
    _parts[1]->set_y(_y - _parts[1] -> get_height() * 0.5);

    _parts[0]->draw_rectangle(window);
    _parts[0]->draw_circle(window);
    _parts[0]->draw_circle(window);
    _knob->draw_circle(window);
    
}