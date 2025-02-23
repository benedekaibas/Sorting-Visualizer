#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <iostream>

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
    for (int i = 0; i < NUM_BARS - 1; i++){
        for (int j = 0; j < NUM_BARS - i - 1; j++){
            if (array[j] > array[j + 1]){
                std::swap(array[j], array[j + 1]);
                display_array(window);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
    }
}

int partition(std::vector<int>& nums, int low, int high) {
    int pivot = nums[high]; // Choosing the last element as pivot
    int i = low - 1; // Index of smaller element

    for (int j = low; j < high; j++) {
        // If current element is smaller than or equal to pivot
        if (nums[j] <= pivot) {
            i++; // Increment index of smaller element
            std::swap(nums[i], nums[j]);
        }
    }
    std::swap(nums[i + 1], nums[high]);
    return i + 1;
}

void quickSort(sf::RenderWindow& window, std::vector<int>& nums, int low, int high) {
    if (low < high) {
        // Partitioning index
        int pi = partition(nums, low, high);

        // Recursively sort elements before and after partition
        quickSort(window, nums, low, pi - 1);
        quickSort(window, nums, pi + 1, high);

        // Display the array after each partition
        display_array(window);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int main(){
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sorting Visualizer in C++");
    generate_array();
    display_array(window);

    int choice;
    std::cout << "Choose sorting algorithm: 1 for Bubble Sort, 2 for Quick Sort: ";
    std::cin >> choice;

    if (choice == 1) {
        std::thread sortingThread(bubble_sort, std::ref(window));
        sortingThread.join();
    } else if (choice == 2) {
        std::thread sortingThread(quickSort, std::ref(window), std::ref(array), 0, NUM_BARS - 1);
        sortingThread.join();
    } else {
        std::cout << "Invalid choice!" << std::endl;
        return 1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    return 0;
}
