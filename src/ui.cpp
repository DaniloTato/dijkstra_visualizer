#include "../include/header.hpp"

ui::ui(int x, int y, int width, int height):
_x(x), _y(y), _width(width), _height(height){

}

void ui::draw_rectangle(sf::RenderWindow& window){

    sf::Vector2f pos = return_position();
    sf::RectangleShape rectangle(sf::Vector2f(_width, _height));
    rectangle.setFillColor(sf::Color(0,0,0));
    rectangle.setPosition(pos.x,pos.y);
    window.draw(rectangle);
}

void ui::draw_circle(sf::RenderWindow& window, sf::Color clr){
    sf::Vector2f pos = return_position();
    sf::CircleShape circle(_height);
    circle.setPosition(pos.x, pos.y);
    circle.setFillColor(clr);
    window.draw(circle);
}

void ui::draw_triangle(sf::RenderWindow& window){
    sf::ConvexShape triangle;
    triangle.setPointCount(3);

    sf::Vector2f pos = return_position();
    int pos_x = pos.x;
    int pos_y = pos.y;

    triangle.setPoint(0, sf::Vector2f(pos_x + _width * 0.5, pos_y)); // arriba
    triangle.setPoint(1, sf::Vector2f(pos_x, pos_y + _height)); // izquierda
    triangle.setPoint(2, sf::Vector2f(pos_x + _width, pos_y + _height)); // derecha
    triangle.setFillColor(sf::Color(0,0,0));
    window.draw(triangle);
}

bool ui::check_mouse_collision(){
    sf::Vector2f my_pos = return_position();

    int object_left = my_pos.x;
    int object_right = object_left + (_height*2) * camera_zoom;
    int object_up = my_pos.y;
    int object_down = object_up + (_height*2) * camera_zoom;
    
    if (mouse_pos.x > object_left && mouse_pos.x < object_right && mouse_pos.y > object_up && mouse_pos.y < object_down){
        return true;
    }
    return false;

}

bool ui::being_clicked(bool right){
    if(right){
        if(check_mouse_collision() && sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            return true;
        }
    } else{
        if(check_mouse_collision() && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            return true;
        }
    }

    return false;

}

void ui::draw(sf::RenderWindow &window){
    
}

void ui::set_x( int x){
    _x = x;
}

void ui::set_y( int y){
    _y = y;
}

int ui::get_x(){
    return _x;
}

sf::Vector2f ui::return_position(){
    return {(float)_x,(float)_y};
}

int ui::get_height(){
    return _height;
}

int ui::get_y(){
    return _y;
}