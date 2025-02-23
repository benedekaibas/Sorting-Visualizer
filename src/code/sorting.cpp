#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

//using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const int NUM_BARS = 50;

std::vector<int> array(NUM_BARS);

void generate_array(){
    for (int i = 0; i < NUM_BARS; i++){
        array[i] = rand() % HEIGHT;
    }
}

void display_array(sf::RenderWindow& window){
    window.clear();
    float bar_width = WIDTH / float(NUM_BARS);

    for (int i = 0; i < NUM_BARS; i++){
        sf::RectangleShape bar(sf::Vector2f(bar_width - 2, array[i]));
        bar.setPosition(i * bar_width, HEIGHT - array[i]);
        bar.setFillColor(sf::Color::White);
        window.draw(bar);
    }
    window.display();
}

void bubble_sort(sf::RenderWindow& window){

}

int main(){
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sorting Visualizer in C++");
    generate_array();
    display_array(window);

    return 0;
}