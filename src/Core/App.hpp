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
    const string MODEL_PATH="../res/models/goodMorning.obj";
    WindowClass window;
    TimeClass time;
    Input input;
    RenderTool renderTool;
    Shaders shaderManager;
    Mesh mesh; //REMOVE ME LATER
    MatrixTransformer transform;
    Camera camera;
    float fovAngle;
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
    fovAngle=7.0f/18.0f*acos(-1);
}

void App::start() {
    if(isRunning)
        return;
    isRunning=true;
    shaderManager.loadVertexShader(VERTEX_SHADER_PATH);
    shaderManager.loadFragmentShader(FRAGMENT_SHADER_PATH);
    shaderManager.compileShaderProgram();
    mesh.setProgramID(shaderManager.getProgramID());

    glutWarpPointer(window.getWidth()/2, window.getHeight()/2);
    glutSetCursor(GLUT_CURSOR_NONE);
    mesh.addVerticesFromModel(MODEL_PATH);
    transform.initProjection(fovAngle, window.getWidth(), window.getHeight(), 0.001f, 1000.0f);
    shaderManager.addUniform("transformMatrix");
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
    //transform.setTranslation(0,0, 0);
    transform.setRotation(acos(-1)/2.0, 0, 0);
    float scale=0.625+0.375*sin(2*timeSec*acos(-1));
    //transform.setScale(scale, scale, scale);
    transform.setCamera(camera);
    shaderManager.setUniform("transformMatrix", transform.getProjectedTransformation());
}
void App::processInput() {
    float scaleSpeed=0.5f;
    float rotateSpeed=0.25f;
    float moveSpeed=0.005f;
    static float scale=1.0f;
    if(input.getMousePos().getX()!=window.getWidth()/2 || input.getMousePos().getY()!=window.getHeight()/2) {
        float moveX=input.getMousePos().getX()-window.getWidth()/2;
        float moveY=input.getMousePos().getY()-window.getHeight()/2;
        float rotateX=2*rotateSpeed*(moveY/(float)window.getHeight())*(fovAngle/2.0f);
        float rotateY=2*rotateSpeed*(moveX/(float)window.getWidth())*(fovAngle/2.0f);
        camera.rotateX(rotateX);
        camera.rotateY(rotateY);
        glutWarpPointer(window.getWidth()/2, window.getHeight()/2);
    }
    if(input.getKeyState('c')) {
        scale-=scaleSpeed;
        camera.move(-1.0f*camera.getUp(), moveSpeed);
    }
    if(input.getKeyState(' ')) {
        scale+=scaleSpeed;
        camera.move(camera.getUp(), moveSpeed);
    }
    if(input.getKeyState('a')) {
        camera.move(camera.getLeft(), moveSpeed);
    }
    if(input.getKeyState('d')) {
        camera.move(camera.getRight(), moveSpeed);
    }
    if(input.getKeyState('w')) {
        camera.move(camera.getForward(), moveSpeed);
    }
    if(input.getKeyState('s')) {
        camera.move(-1.0f*camera.getForward(), moveSpeed);
    }
    if(input.getKeyState('q')) {
        camera.rotateZ(0.01*rotateSpeed);
    }
    if(input.getKeyState('e')) {
        camera.rotateZ(-0.01*rotateSpeed);
    }
    if(input.getKeyState(27)) { //esc
        glutLeaveMainLoop();
    }
    if(input.getKeyState('z')) {
        fovAngle-=acos(-1)/360.0;
        transform.initProjection(fovAngle, window.getWidth(), window.getHeight(), 0.001f, 1000.0f);

    }
    if(input.getKeyState('x')) {
        fovAngle+=acos(-1)/360.0;
        transform.initProjection(fovAngle, window.getWidth(), window.getHeight(), 0.001f, 1000.0f);

    }
}
