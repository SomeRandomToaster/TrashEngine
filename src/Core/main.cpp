#include <GL/glxew.h>
#include <GL/glew.h>


#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>
#include "../Utils/RenderUtils.hpp"
#include "../Utils/Time.hpp"
#include "../Utils/ResourceLoader.hpp"
#include "Window.hpp"
#include "../Math/Vectors.hpp"
#include "../Utils/Input.hpp"
#include "../Graphics/Vertex.hpp"
#include "../Graphics/Mesh.hpp"
#include "App.hpp"

const int WIDTH=800;
const int HEIGHT=600;
const string TITLE="TrashEngine";



int main() {
    WindowClass window(WIDTH, HEIGHT, TITLE);
    App testApp(window);
    testApp.start();
    return 0;
}
