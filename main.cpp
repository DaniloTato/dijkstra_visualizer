#include "./include/header.hpp"
#include "src/functions.cpp"
#include "src/ui.cpp"
#include "src/camera_sensitive.cpp"
#include "src/node.cpp"

int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;
int camera_x = 0;
int camera_y = 0;
sf::Vector2i mouse_pos;
sf::Vector2i mouse_pos_last_frame;
float last_frame_mouse_wheel = 0;
int go_to_camera_x = -100;
int go_to_camera_y = -100;
float camera_zoom = 1;
float go_to_camera_zoom = 1;
int resized_window_width = SCREEN_WIDTH;
int resized_window_height = SCREEN_HEIGHT;
bool click_block = false;
bool right_click_block = false;
unsigned long frames;
node* selected = nullptr;
std::string info_string;
int to_edit = 0;
unsigned long text_frames;
int show_invalid_text_message = 0;
int dijkstra_text_height = 0;

std::vector<std::vector<std::pair<int,int>>> paths_taken;

std::string input;


int main(){
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Typing RPG");
    window.setFramerateLimit(120);

    //se carga la fuente a un objeto de sfml
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font\n";
        return -1;
    }

    //se asigna fuente al texto que mostrará los fps del proyecto
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color::Black);
    fpsText.setPosition(10, 10);

    sf::Text info;
    info.setFont(font);
    info.setCharacterSize(15);
    info.setFillColor(sf::Color::Black);

    sf::Text create_chords;
    create_chords.setFont(font);
    create_chords.setCharacterSize(20);



    sf::Clock clock;

    float lastTime = 0;
    int frame_count = 0;
    float fps = 0;

    int starting_node = 0;

    std::vector<node*> node_vector;
    node_vector.push_back(new node(100,100, 100, 100,20));
    node_vector.back() -> update_name(node_vector);
    node_vector.push_back(new node(150,0, 150, 0, 20));
    node_vector.back() -> update_name(node_vector);
    node_vector.push_back(new node(150,200,150,200, 20));
    node_vector.back() -> update_name(node_vector);
    node_vector.push_back(new node(300,300,300,300, 20));
    node_vector.back() -> update_name(node_vector);
    node_vector.push_back(new node(500,100,500,100, 20));
    node_vector.back() -> update_name(node_vector);

    while (window.isOpen()){

        frames++;
        text_frames++;

        mouse_pos = sf::Mouse::getPosition(window);

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::Resized){
                sf::FloatRect view(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(view));
                resized_window_width = event.size.width;
                resized_window_height = event.size.height;
            }

            if(event.type == sf::Event::MouseWheelMoved){
                if(event.mouseWheel.delta > 0){
                    go_to_camera_zoom += 0.04;
                } else if(event.mouseWheel.delta < 0) go_to_camera_zoom -= 0.04;
            }

            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Right){
                    to_edit++;
                    if(to_edit > node_vector.size() - 1) to_edit = 0;
                    frames = 0;
                    go_to_camera_x = node_vector[to_edit] -> get_x() - resized_window_width*0.5 + node_vector[to_edit] -> get_x()*(camera_zoom - 1);
                    go_to_camera_y = node_vector[to_edit] -> get_y() - resized_window_height*0.5 + node_vector[to_edit] -> get_y()*(camera_zoom - 1);
                }else if(event.key.code == sf::Keyboard::Left){
                    to_edit--;
                    if(to_edit < 0) to_edit = node_vector.size() - 1;
                    frames = 0;
                    go_to_camera_x = node_vector[to_edit] -> get_x() - resized_window_width*0.5 + node_vector[to_edit] -> get_x()*(camera_zoom - 1);
                    go_to_camera_y = node_vector[to_edit] -> get_y() - resized_window_height*0.5 + node_vector[to_edit] -> get_y()*(camera_zoom - 1);
                }

                if (event.key.code == sf::Keyboard::Space){
                    input += " ";
                    text_frames = 0;
                }

                if (event.key.code == sf::Keyboard::Enter){
                    text_frames = 0;
                    auto opt_tup = get_input_tuple(input);
                    if (opt_tup.has_value()) {
                        auto& tup = opt_tup.value();
                        node_vector.push_back(new node(std::get<0>(tup),std::get<1>(tup),std::get<0>(tup),std::get<1>(tup),20,std::get<2>(tup)));

                        update_all_names(node_vector);

                        info_string = make_info_text(node_vector, starting_node, paths_taken);
                        dijkstra_text_height = 17 * node_vector.size();

                    } else {
                        show_invalid_text_message = 60;
                    }
                    input.clear();
                }

                if(event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift){
                    starting_node = to_edit;
                    info_string = make_info_text(node_vector, starting_node, paths_taken);
                    dijkstra_text_height = 17 * node_vector.size();
                }

                if(event.key.code == sf::Keyboard::BackSpace){
                    if(selected){
                        selected -> _has_temp_vector = 0;
                        selected = nullptr;
                    
                    }
                }

                if(event.key.code == sf::Keyboard::Tab){
                    if(node_vector.size() > 1){
                        for(auto i: node_vector){
                            for(int j = 0; j < i->_paths.size(); j++){
                                if(i->_paths[j].first == to_edit){
                                   i->_paths.erase(i->_paths.begin() + j);
                                   j--;
                                }
                            }
                        }
                        delete node_vector[to_edit];
                        node_vector.erase(node_vector.begin() + to_edit);

                        update_all_names(node_vector);

                        info_string = make_info_text(node_vector, starting_node, paths_taken);
                        dijkstra_text_height = 17 * node_vector.size();

                        to_edit--;
                        if(to_edit < 0) to_edit = node_vector.size() - 1;
                    }
                }
 
            }

            if(event.type == sf::Event::TextEntered){
                char ch = static_cast<char>(event.text.unicode);

                if (ch == '\b' && !input.empty()) {
                    input.pop_back();
                    text_frames = 0;
                } else if (std::isdigit(ch)||std::isalpha(ch)||ch == '-'){
                    input += ch;
                    text_frames = 0;
                }
            }

        }

        camera_zoom += (go_to_camera_zoom - camera_zoom) * 0.1;
        camera_x += (go_to_camera_x - camera_x) * 0.1;
        camera_y += (go_to_camera_y - camera_y) * 0.1;

        // fps counter

        float current_time = clock.getElapsedTime().asSeconds();
        frame_count++;

        if (current_time - lastTime >= 1.0) {
            fps = frame_count / (current_time - lastTime);

            lastTime = current_time;
            frame_count = 0;
        }

        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));

        //draw phase

        for (int i = 0; i < node_vector.size(); i++){
            if(node_vector[i] -> being_clicked() && !click_block){
                click_block = true;
                if(!selected){
                    //mode when selecting
                    node_vector[i] -> _has_temp_vector = 1;
                    selected = node_vector[i];
                } else if (node_vector[i] != selected){
                    //mode when assigning
                    selected -> _has_temp_vector = 0;
                    selected -> _paths.push_back({i,get_magnitude(selected -> get_geo_chords(),node_vector[i] -> get_geo_chords())});
                    selected = nullptr;
                    info_string = make_info_text(node_vector, starting_node, paths_taken);
                    dijkstra_text_height = 17 * node_vector.size();
                }
                to_edit = i;
            }

            if(node_vector[i] -> being_clicked(true) && !right_click_block){
                starting_node = i;
                info_string = make_info_text(node_vector, starting_node, paths_taken);
                dijkstra_text_height = 17 * node_vector.size();
            }
        }

        if(!selected && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            go_to_camera_x -= mouse_pos.x - mouse_pos_last_frame.x;
            go_to_camera_y -= mouse_pos.y - mouse_pos_last_frame.y;
        }

        mouse_pos_last_frame = mouse_pos;
        last_frame_mouse_wheel = event.mouseWheel.delta;

        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) right_click_block = true;
        else right_click_block = false;

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) click_block = true;
        else click_block = false;

        info.setPosition(resized_window_width - 230, resized_window_height - 50 - dijkstra_text_height);
        info.setString(info_string);

        //setting position and string of the input text
        if(show_invalid_text_message) show_invalid_text_message--;

        create_chords.setPosition(20, resized_window_height - 50);
        if(!show_invalid_text_message){
            create_chords.setFillColor(sf::Color::Black);
            if((int)text_frames/60 % 2 == 0) create_chords.setString("New node at: " + input + "@");
            else create_chords.setString("New node at: " + input);
        }else{
            create_chords.setFillColor(sf::Color(228,0,124));
            create_chords.setString("Invalid format.");
        }

        window.clear(sf::Color::White);

        if(node_vector.size()){
            int radius = 26 - sinf(frames/50.0f) * 2;
            camera_sensitive selection_circle(node_vector[to_edit] -> get_x() - (radius - 20), node_vector[to_edit] -> get_y() - (radius - 20), radius, radius);
            selection_circle.draw_circle(window, sf::Color(255,210,0));
        }

        //drawing all arrows and nodes
        int counter = 0;
        std::vector<std::pair<sf::Vector2f,sf::Vector2f>> lines_drawn;
        lines_drawn.clear();
        for(auto i: node_vector){
            sf::Vector2f my_pos = i -> return_position();

            for(auto j: i -> _paths){

                sf::Color line_color;
                if(found_in_vector(paths_taken[counter], j)) line_color = sf::Color(228,0,124);
                else line_color = sf::Color::Black;

                //line
                sf::Vector2f target_pos = node_vector[j.first] -> return_position();

                float to_center = i -> get_height() * camera_zoom;
                sf::Vector2f start(my_pos.x + to_center, my_pos.y + to_center);
                sf::Vector2f end(target_pos.x + to_center, target_pos.y + to_center);

                
                sf::VertexArray line(sf::Lines, 2);

                line[0].position = end;
                line[0].color = line_color;
                line[1].position = start;
                line[1].color = line_color;

                if(!find_line_in_vector(lines_drawn, line)){
                    window.draw(line);
                    lines_drawn.push_back(std::make_pair(start,end));
                } else if(line_color == sf::Color(228,0,124)){
                    window.draw(line);
                }

                //triangle for arrow

                sf::Vector2f direction = end - start;
                float angle = std::atan2(direction.y, direction.x);

                sf::ConvexShape arrowhead;
                arrowhead.setPointCount(3);

                int head_size = 5 * camera_zoom;

                int magnitude = get_magnitude(start, end) - to_center;
                sf::Vector2f end_minus_radius(start.x + magnitude * std::cos(angle), start.y + magnitude * std::sin(angle));

                arrowhead.setPoint(0, end_minus_radius);
                arrowhead.setPoint(1, end_minus_radius - sf::Vector2f(head_size * std::cos(angle + M_PI / 6), head_size * std::sin(angle + M_PI / 6)));
                arrowhead.setPoint(2, end_minus_radius - sf::Vector2f(head_size * std::cos(angle - M_PI / 6), head_size * std::sin(angle - M_PI / 6)));
                arrowhead.setFillColor(sf::Color::Black);

                window.draw(arrowhead);
            }

            if(i -> _has_temp_vector){
                sf::VertexArray temp_line(sf::Lines, 2);

                float to_center = i -> get_height() * camera_zoom;
                temp_line[0].position = sf::Vector2f(my_pos.x + to_center, my_pos.y + to_center);
                temp_line[0].color = sf::Color::Black;
                temp_line[1].position = sf::Vector2f(mouse_pos.x, mouse_pos.y);
                temp_line[1].color = sf::Color::Black;

                window.draw(temp_line);
            }
            counter++;
        }

        for(int i = 0; i < node_vector.size(); i++){
            if(i == starting_node) node_vector[i] -> draw_circle(window, sf::Color(228,0,124));
            else node_vector[i] -> draw_circle(window);
        }

        window.draw(fpsText);
        window.draw(info);
        window.draw(create_chords);
        window.display();

    }

    return 0;
}