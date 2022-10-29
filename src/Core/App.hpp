//
// Created by leo on 08/10/22.
//

#ifndef TRASHENGINE_MAINCYCLE_HPP
#define TRASHENGINE_MAINCYCLE_HPP

#endif //TRASHENGINE_MAINCYCLE_HPP

class App;
App* currentAppInstance;

class App {
    const int MAX_FPS=240;
    const string VERTEX_SHADER_PATH="../src/Graphics/Shaders/VertexShader.glsl";
    const string FRAGMENT_SHADER_PATH="../src/Graphics/Shaders/FragmentShader.glsl";
    WindowClass window;
    TimeClass time;
    Input input;
    RenderTool renderTool;
    ResourceLoader loader;
    Mesh mesh; //REMOVE ME LATER
    bool isRunning;
    unsigned long long lastTime;
    double unprocessedTime;
    double frameTimeCounter;
    double frameTime;
    int frameCounter;
    static void loopCallback();
    void setupStaticAppFunctions();
public:
    App(WindowClass& window);
    void start();
    void stop();
    void run();
    void render();
    void cleanUp();
    void update();
    void processInput();
};

App::App(WindowClass& window) : window(window) {
    setupStaticAppFunctions();
    isRunning=false;
    lastTime=time.getTime();
    unprocessedTime=0;
    frameTimeCounter=0;
    frameCounter=0;
    frameTime=1/(double)MAX_FPS;
}

void App::start() {
    if(isRunning)
        return;
    isRunning=true;
    loader.loadVertexShader(VERTEX_SHADER_PATH);
    loader.loadFragmentShader(FRAGMENT_SHADER_PATH);
    loader.compileShaderProgram();
    mesh.setProgramID(loader.getProgramID());
    //REMOVE ME LATER
    vector<Vertex> data {
        Vertex(vector3f(-1,-1,0)),
        Vertex(vector3f(0,1,0)),
        Vertex(vector3f(1,-1,0)),
    };
    mesh.addVertices(data);
    //REMOVE ME LATER ^

    glutMainLoop();

    stop();
}

void App::stop() {
    isRunning=false;
    cleanUp();
}

void App::run() {
    bool render= false;
    unsigned long long startTime = time.getTime();
    unsigned long long passedTime=startTime-lastTime;
    lastTime=startTime;

    unprocessedTime+=passedTime/time.SECOND;
    frameTimeCounter+=passedTime;

    while(unprocessedTime>frameTime) {
        render=true;
        unprocessedTime-=frameTime;
        time.setDelta(frameTime);

        //UPDATE
        processInput();
        update();

        if(frameTimeCounter>=time.SECOND) {
            std::cout << frameCounter << std::endl;
            frameCounter=0;
            frameTimeCounter=0;
        }
    }
    if(render) {
        this->render();
        frameCounter++;
    }
}

void App::render() {
    renderTool.clearScreen();
    mesh.draw();
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
void App::update() {

}
void App::processInput() {

}
