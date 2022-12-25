//
// Created by leo on 13/10/22.
//

#ifndef TRASHENGINE_INPUT_HPP
#define TRASHENGINE_INPUT_HPP

#endif //TRASHENGINE_INPUT_HPP

#define LEFT_MOUSE_BUTTON 0
#define MIDDLE_MOUSE_BUTTON 1
#define RIGHT_MOUSE_BUTTON 2

#define ESCAPE_KEY 27

class Input;
Input* currentInputInstance;

class Input {
    bool keyState[256];
    bool unprocessedKeys[256];
    bool mouseState[3];
    bool unprocessedMouse[3];
    int mouseX, mouseY;
    bool cursorLocked;
    void setupStaticInputFunctions();
    static void normalKeyDownCallback(unsigned char key, int x, int y);
    void normalKeyDown(unsigned char key, int x, int y);
    static void normalKeyUpCallback(unsigned char key, int x, int y);
    void normalKeyUp(unsigned char key, int x, int y);
    static void mouseClickCallback(int button, int state, int x, int y);
    void mouseClick(int button, int state, int x, int y);
    static void passiveMouseCallback(int x, int y);
    void passiveMouseMove(int x, int y);
public:
    Input();
    bool getKeyState(char key);
    bool getKeyDown(char key);
    bool getKeyUp(char key);
    bool getMouseButtonState(int button);
    bool getMouseButtonDown(int button);
    bool getMouseButtonUp(int button);
    vector2f getMousePos();

    void setMousePos(const int x, const int y);
    void setCursor(const bool enable);
    void lockCursor();
    void unlockCursor();
    bool getCursorLocked();
};
Input::Input() {
    for(int i=0; i<256; i++) {
        keyState[i]=false;
        unprocessedKeys[i]=false;
    }
    for(int i=0; i<3; i++) {
        mouseState[i]=false;
        unprocessedMouse[i]=false;
    }
    glutIgnoreKeyRepeat(1);
    setupStaticInputFunctions();
    cursorLocked=false;
}
void Input::setupStaticInputFunctions() {
    currentInputInstance = this;
    ::glutKeyboardFunc(Input::normalKeyDownCallback);
    ::glutKeyboardUpFunc(Input::normalKeyUpCallback);
    ::glutMouseFunc(Input::mouseClickCallback);
    ::glutPassiveMotionFunc(Input::passiveMouseCallback);
}

void Input::normalKeyDownCallback(unsigned char key, int x, int y) {
    currentInputInstance->normalKeyDown(key, x, y);
}
void Input::normalKeyDown(unsigned char key, int x, int y) {
    keyState[key]=true;
    unprocessedKeys[key]=true;
}
void Input::normalKeyUpCallback(unsigned char key, int x, int y) {
    currentInputInstance->normalKeyUp(key, x, y);
}
void Input::normalKeyUp(unsigned char key, int x, int y) {
    keyState[key]=false;
    unprocessedKeys[key]=true;
}
bool Input::getKeyState(char key) {
    unprocessedKeys[key]=false;
    return keyState[key];
}
bool Input::getKeyDown(char key) {
    if(unprocessedKeys[key] && keyState[key]) {
        unprocessedKeys[key]=false;
        return true;
    }
    return false;
}
bool Input::getKeyUp(char key) {
    if(unprocessedKeys[key] && !keyState[key]) {
        unprocessedKeys[key]=false;
        return true;
    }
    return false;
}
void Input::mouseClickCallback(int button, int state, int x, int y) {
    currentInputInstance->mouseClick(button, state, x, y);
}
void Input::mouseClick(int button, int state, int x, int y) {
    mouseX=x;
    mouseY=y;
    int buttonIdx=-1;
    if(button==GLUT_LEFT_BUTTON)
        buttonIdx=0;
    if(button==GLUT_MIDDLE_BUTTON)
        buttonIdx=1;
    if(button==GLUT_RIGHT_BUTTON)
        buttonIdx=2;
    if(buttonIdx>=0) {
        if (state == GLUT_DOWN)
            mouseState[buttonIdx] = true;
        else if (state == GLUT_UP)
            mouseState[buttonIdx] = false;
        unprocessedMouse[buttonIdx] = true;
    }
}
void Input::passiveMouseCallback(int x, int y) {
    currentInputInstance->passiveMouseMove(x, y);
}
void Input::passiveMouseMove(int x, int y) {
    mouseX=x;
    mouseY=y;
}
bool Input::getMouseButtonState(int button) {
    unprocessedMouse[button]=false;
    return mouseState[button];
}
bool Input::getMouseButtonDown(int button) {
    if(unprocessedMouse[button] && mouseState[button]) {
        unprocessedMouse[button]=false;
        return true;
    }
    return false;
}
bool Input::getMouseButtonUp(int button) {
    if(unprocessedMouse[button] && !mouseState[button]) {
        unprocessedMouse[button]=false;
        return true;
    }
    return false;
}
vector2f Input::getMousePos() {
    return vector2f(mouseX, mouseY);
}
void Input::setMousePos(const int x, const int y) {
    glutWarpPointer(x, y);
}
void Input::setCursor(const bool enable) {
    if(enable)
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    else
        glutSetCursor(GLUT_CURSOR_NONE);
}
void Input::lockCursor() {
    cursorLocked=true;
    setCursor(false);
}
void Input::unlockCursor() {
    cursorLocked=false;
    setCursor(true);
}
bool Input::getCursorLocked() {
    return cursorLocked;
}