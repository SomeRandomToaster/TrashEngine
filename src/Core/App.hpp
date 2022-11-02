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
    Shaders shaderManager;
    Mesh mesh; //REMOVE ME LATER
    MatrixTransformer transform;
    bool isRunning;
    unsigned long long lastTime;
    double unprocessedTime;
    double frameTimeCounter;
    double frameTime;
    int frameCounter;
    unsigned long long appStartTime;
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
    shaderManager.loadVertexShader(VERTEX_SHADER_PATH);
    shaderManager.loadFragmentShader(FRAGMENT_SHADER_PATH);
    shaderManager.compileShaderProgram();
    mesh.setProgramID(shaderManager.getProgramID());
    //REMOVE ME LATER
    /*vector<Vertex> data {
        Vertex(vector3f(-1,-1,0)),
        Vertex(vector3f(0,1,0)),
        Vertex(vector3f(1,-1,0)),
    };*/
    vector<Vertex> data {
        Vertex(vector3f(-0.5,-sqrt(3)/6,0)),
        Vertex(vector3f(0,sqrt(3)/3,0)),
        Vertex(vector3f(0.5,-sqrt(3)/6,0)),
    };
    mesh.addVertices(data);
    //REMOVE ME LATER ^
    shaderManager.addUniform("transformMatrix");
    //transform.setTranslation(0.5, 0.25, 0);
    //transform.addTranslation(1, 0, 0);
    //transform.addTranslation(-0.5, 0, 0);
    appStartTime=time.getTime();
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
    long double timeSec=(time.getTime()-appStartTime)/(long double)1e9;
    transform.setTranslation(sin(timeSec*acos(-1)),0, 0);
    transform.setRotation(0, 0, 2*acos(-1)*timeSec);
    float scale=0.625+0.375*sin(2*timeSec*acos(-1));
    transform.setScale(scale, scale, scale);
    shaderManager.setUniform("transformMatrix", transform.getMatrix());
}
void App::processInput() {

}
