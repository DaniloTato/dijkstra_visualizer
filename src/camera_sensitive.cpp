#include "../include/header.hpp"

camera_sensitive::camera_sensitive(int x, int y, int width, int height, float paralax):
_paralax(paralax), ui(x,y,width,height){

}

void camera_sensitive::draw_rectangle(sf::RenderWindow& window){
    sf::Vector2f pos = return_position();
    sf::RectangleShape rectangle(sf::Vector2f(_width * camera_zoom, _height * camera_zoom));
    rectangle.setFillColor(sf::Color(0,0,0));
    rectangle.setPosition(pos.x,pos.y);
    window.draw(rectangle);
}

void camera_sensitive::draw_circle(sf::RenderWindow& window, sf::Color clr){
    sf::Vector2f pos = return_position();
    sf::CircleShape circle(_height*camera_zoom);
    circle.setPosition(pos.x, pos.y);
    circle.setFillColor(clr);
    window.draw(circle);
}

sf::Vector2f camera_sensitive::return_position(){
    int x_with_diff = _x;
    int y_with_diff = _y;
    
    int sum_due_to_parallax_x = ((-2 + SCREEN_WIDTH * (-1 + _paralax)) / (2 * _paralax) + 1);
    int sum_due_to_parallax_y = ((-2 + SCREEN_HEIGHT * (-1 + _paralax)) / (2 * _paralax) + 1);

    int sum_due_to_zoom_x = (camera_zoom - 1)* (x_with_diff + sum_due_to_parallax_x);
    int sum_due_to_zoom_y = (camera_zoom - 1)* (y_with_diff + sum_due_to_parallax_x);

    return {(x_with_diff - (camera_x/_paralax) + sum_due_to_zoom_x + sum_due_to_parallax_x),
            (y_with_diff - (camera_y /_paralax) + sum_due_to_zoom_y + sum_due_to_parallax_y)};
}