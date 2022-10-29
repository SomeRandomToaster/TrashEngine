//
// Created by leo on 08/10/22.
//

#ifndef TRASHENGINE_WINDOW_HPP
#define TRASHENGINE_WINDOW_HPP

#endif //TRASHENGINE_WINDOW_HPP

using namespace std;

class WindowClass;
static WindowClass* currentWindowInstance;

class WindowClass {
    int width, height;
    string title;
    void setupStaticWindowFunctions();
    static void displayCallback();
public:
    WindowClass(const int width, const int height, const string& title);
    int getWidth();
    int getHeight();
    string getTitle();
    void render();
    void destroy();
};

WindowClass::WindowClass(const int width, const int height, const string& title) {
    this->width=width;
    this->height=height;
    this->title=title;
    int argc=0;
    char** argv=nullptr;
    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(title.c_str());
    glClearColor(0,0,0, 0);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glewInit();
    setupStaticWindowFunctions();
}
int WindowClass::getWidth() {
    return width;
}
int WindowClass::getHeight() {
    return height;
}
string WindowClass::getTitle() {
    return title;
}
void WindowClass::render() {

    glutSwapBuffers();
}

void WindowClass::displayCallback() {
    currentWindowInstance->render();
}

void WindowClass::setupStaticWindowFunctions() {
    currentWindowInstance = this;
    ::glutDisplayFunc(WindowClass::displayCallback);
}

void WindowClass::destroy() {
    glutDestroyWindow(glutGetWindow());
}