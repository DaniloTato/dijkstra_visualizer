#ifndef FUNCTIONS
#define FUNCTIONS

#include "../include/header.hpp"

void print_vector(std::vector<int> &vec){
    std::cout << "[ ";
    for (auto i: vec){
        std::cout << i << ", ";
    }
    std::cout << " ]" << "\n";
}

template<typename T>
void clear_and_delete(std::vector<T> &vec){
    for(T i : vec){
        delete i;
    }
    vec.clear();
}

const int INF = std::numeric_limits<int>::max();

std::pair<std::vector<int>, std::vector<std::vector<std::pair<int,int>>>> dijkstra(int n, int origen, const std::vector<node*>& grafo) {
    // Vector de distancias, inicializado en "infinito" para todos los nodos
    std::vector<int> distancias(n, INF);
    distancias[origen] = 0;

    std::vector<std::vector<std::pair<int,int>>> paths_taken(n);

    // Cola de prioridad para seleccionar el nodo con la distancia mínima
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, origen}); // La cola almacena pares {distancia, nodo}

    while (!pq.empty()) {
        int distancia_actual = pq.top().first; // distancia minima actual
        int nodo_actual = pq.top().second; // nodo esa distancia
        pq.pop(); // sacar el elemento

        // Ignoramos nodos ya procesados
        if (distancia_actual > distancias[nodo_actual]) continue;

        // Exploramos los vecinos del nodo actual
        for (const auto& vecino : grafo[nodo_actual] -> _paths) {
            int nodo_vecino = vecino.first;
            int peso_arista = vecino.second;

            // Calculamos la nueva distancia al vecino
            int nueva_distancia = distancia_actual + peso_arista;

            if (nueva_distancia < distancias[nodo_vecino]) {
                distancias[nodo_vecino] = nueva_distancia;
                paths_taken[nodo_actual].push_back(std::make_pair(nodo_vecino, nueva_distancia - distancia_actual));
                pq.push({nueva_distancia, nodo_vecino});
            }
        }
    }

    return std::make_pair(distancias, paths_taken);
}


float get_magnitude(const sf::Vector2f& pointA, const sf::Vector2f& pointB) {
    float dx = pointB.x - pointA.x;
    float dy = pointB.y - pointA.y;
    return std::sqrt(dx * dx + dy * dy);
}

std::optional<std::tuple<int, int, std::string>> get_input_tuple(const std::string& input) {
    std::istringstream stream(input);
    int first, second;
    std::string name;
    if (!(stream >> first)) {
        return std::nullopt;
    }
    if (!(stream >> second)) {
        return std::nullopt;
    }
    if (!(stream >> name)) {
        name = "#default_node";
    }

    return std::make_tuple(first, second, name);
}

std::string make_info_text(const std::vector<node*>& grafo, int origen, std::vector<std::vector<std::pair<int,int>>>& paths_taken){
    std::pair<std::vector<int>, std::vector<std::vector<std::pair<int,int>>>> res = dijkstra(grafo.size(), origen, grafo);
    std::vector<int> distancias =  res.first;
    paths_taken = res.second;

    std::string str;
    str += "Distancias desde el nodo " + std::to_string(origen) + ":\n";
    for (int i = 0; i < distancias.size(); ++i) {
        if (distancias[i] == INF)
            str += grafo[i] -> _name + ": Inalcanzable\n";
        else
            str += grafo[i] -> _name + ": " + std::to_string(distancias[i]) + "\n";
    }
    return str;
}

bool found_in_vector(const std::vector<std::pair<int,int>>& vec, const std::pair<int,int>& target){
    for (auto i: vec){
        if(i == target) return true;
    }
    return false;
}

bool found_in_vector(const std::vector<node*>& vec, const std::string& target, node* ptr){
    for(auto i: vec){
        if(i -> _name == target && i != ptr){
            return true;
        }
    }
    return false;
}

bool find_line_in_vector(const std::vector<std::pair<sf::Vector2f,sf::Vector2f>>& vec, sf::VertexArray& target){
    for (auto i: vec){
        if((i.first == target[0].position && i.second == target[1].position)||(i.first == target[1].position && i.second == target[0].position)){
            return true;
        }
    }
    return false;
}

void update_all_names(std::vector<node*> node_vector){
    for(auto i: node_vector){
        i -> update_name(node_vector);
    }
}

#endif