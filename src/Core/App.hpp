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
    const string MODEL_PATH="../res/models/iWantPizza.obj";
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
        Vertex(vector3f(0,-1,1)),
    };*/
    vector<Vertex> data {
        Vertex(vector3f(-0.5,-1/sqrt(6),-sqrt(3)/6)),
        Vertex(vector3f(0.5, -1/sqrt(6), -sqrt(3)/6)),
        Vertex(vector3f(0, -1/sqrt(6), sqrt(3)/3)),
        Vertex(vector3f(0, sqrt(3)/2-1/sqrt(6), 0)),
    };
    vector<GLuint> indices {
        1, 3, 0,
        0, 3, 2,
        2, 3, 1,
        0, 2, 1
    };
    mesh.addVerticesFromModel(MODEL_PATH);
    //mesh.addVertices(data, indices);
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
    renderTool.clearScreen(0.25, 0.25, 0.25);
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
    //transform.setTranslation(sin(timeSec*acos(-1)),0, 0);
    //transform.setRotation(timeSec*acos(-1), timeSec*acos(-1), 0);
    float scale=0.625+0.375*sin(2*timeSec*acos(-1));
    //transform.setScale(scale, scale, scale);
    shaderManager.setUniform("transformMatrix", transform.getMatrix());
}
void App::processInput() {
    float scaleSpeed=0.005f;
    float rotateSpeed=1.0f;
    static float scale=1.0f;
    static float rotationX=0.0f;
    static float rotationY=0.0f;
    if(input.getKeyState('z')) {
        scale-=scaleSpeed;
        transform.setScale(scale, scale, scale);
    }
    if(input.getKeyState('x')) {
        scale+=scaleSpeed;
        transform.setScale(scale, scale, scale);
    }
    if(input.getKeyState('a')) {
        rotationY+=rotateSpeed*acos(-1)/180;
        transform.setRotation(rotationX, rotationY, 0);
    }
    if(input.getKeyState('d')) {
        rotationY-=rotateSpeed*acos(-1)/180;
        transform.setRotation(rotationX, rotationY, 0);
    }
    if(input.getKeyState('w')) {
        rotationX+=rotateSpeed*acos(-1)/180;
        transform.setRotation(rotationX, rotationY, 0);
    }
    if(input.getKeyState('s')) {
        rotationX-=rotateSpeed*acos(-1)/180;
        transform.setRotation(rotationX, rotationY, 0);
    }
}
