#include <iostream>
#include <chrono>
#include "Time.hpp"
#include "Window.hpp"
#include "Vectors.hpp"
#include "Input.hpp"
#include "App.hpp"

const int WIDTH=800;
const int HEIGHT=600;
const string TITLE="TrashEngine";



int main() {
    Window window(WIDTH, HEIGHT, TITLE);
    App testApp(window);
    testApp.start();
    return 0;
}
