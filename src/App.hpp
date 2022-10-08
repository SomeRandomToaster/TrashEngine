//
// Created by leo on 08/10/22.
//

#ifndef TRASHENGINE_MAINCYCLE_HPP
#define TRASHENGINE_MAINCYCLE_HPP

#endif //TRASHENGINE_MAINCYCLE_HPP

class App;
App* currentAppInstance;

class App {
    Window window;
    static void loopCallback();
    void setupStaticAppFunctions();
public:
    App(Window& window);
    void start();
    void stop();
    void run();
    void render();
    void cleanUp();
};

App::App(Window& window) : window(window) {
    setupStaticAppFunctions();
}

void App::start() {
    run();
    glutMainLoop();
}

void App::stop() {

}

void App::run() {
    render();
}

void App::render() {
    window.render();
}

void App::cleanUp() {

}
void App::loopCallback() {
    currentAppInstance->run();
}

void App::setupStaticAppFunctions()
{
    currentAppInstance = this;
    ::glutIdleFunc(App::loopCallback);
}
