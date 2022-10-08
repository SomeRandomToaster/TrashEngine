//
// Created by leo on 08/10/22.
//

#ifndef TRASHENGINE_WINDOW_HPP
#define TRASHENGINE_WINDOW_HPP

#endif //TRASHENGINE_WINDOW_HPP

#include <GL/glut.h>
#include <string>

using namespace std;

class Window;
static Window* currentWindowInstance;

class Window {
    int width, height;
    string title;
    void setupStaticWindowFunctions();
    static void displayCallback();
public:
    Window(const int width, const int height, const string& title);
    ~Window();
    int getWidth();
    int getHeight();
    string getTitle();
    void render();
};

Window::Window(const int width, const int height, const string& title) {
    this->width=width;
    this->height=height;
    this->title=title;
    int argc=0;
    char** argv=nullptr;
    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(title.c_str());
    glClearColor(0,0,0, 0);
    setupStaticWindowFunctions();
}
int Window::getWidth() {
    return width;
}
int Window::getHeight() {
    return height;
}
string Window::getTitle() {
    return title;
}
void Window::render() {
    glClearColor(0,1,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glutSwapBuffers();
}
Window::~Window() {
    glutDestroyWindow(glutGetWindow());
}
void Window::displayCallback() {
    currentWindowInstance->render();
}

void Window::setupStaticWindowFunctions()
{
    currentWindowInstance = this;
    ::glutDisplayFunc(Window::displayCallback);
}