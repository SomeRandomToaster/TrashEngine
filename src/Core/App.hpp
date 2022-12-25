//
// Created by leo on 08/10/22.
//

#ifndef TRASHENGINE_MAINCYCLE_HPP
#define TRASHENGINE_MAINCYCLE_HPP

#endif //TRASHENGINE_MAINCYCLE_HPP

#define Pi acos(-1)

class App;
App* currentAppInstance;

class App {
    const int MAX_FPS=240;
    const string MODEL_PATH="../res/models/statueOfLiberty.obj";
    const string TEXTURE_PATH="../res/textures/geo2.bmp";
    WindowClass window;
    TimeClass time;
    Input input;
    RenderTool renderTool;
    ResourceLoader resLoader;
    MatrixTransformer transform;
    BasicShader shader;
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

App::App(WindowClass& window) :
    window(window),
    resLoader(TEXTURE_PATH)

    {
    setupStaticAppFunctions();
    isRunning=false;
    lastTime=time.getTime();
    unprocessedTime=0;
    frameTimeCounter=0;
    frameCounter=0;
    frameTime=1/(double)MAX_FPS;
    fovAngle=7.0f/18.0f*Pi;
}

void App::start() {
    if(isRunning)
        return;
    isRunning=true;

    resLoader.mesh.addVerticesFromModel(MODEL_PATH);

    transform.initProjection(fovAngle, window.getWidth(), window.getHeight(), 0.001f, 100.0f);
    transform.setRotation(-Pi/2.0, 0, 0);

    input.setMousePos(window.getWidth()/2, window.getHeight()/2);
    input.lockCursor();

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
    resLoader.material.texture.bind();
    resLoader.mesh.setProgramId(shader.getProgramId());
    resLoader.mesh.draw();
    window.render();
    resLoader.material.texture.unbind();
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
    transform.setCamera(camera);
    shader.updateUniforms(transform.getProjectedTransformation(), vector3f(1, 1, 1));
}
void App::processInput() {
    float scaleSpeed=0.5f;
    float rotateSpeed=0.25f;
    float moveSpeed=0.005f;
    static float scale=1.0f;
    if(input.getMouseButtonState(LEFT_MOUSE_BUTTON)) {
        if(!input.getCursorLocked()) {
            input.setMousePos(window.getWidth() / 2, window.getHeight() / 2);
            input.lockCursor();
        }
    }
    if(input.getMouseButtonState(RIGHT_MOUSE_BUTTON)) {
        input.unlockCursor();
    }
    if(input.getCursorLocked()) {
        if (input.getMousePos().getX() != window.getWidth() / 2 ||
            input.getMousePos().getY() != window.getHeight() / 2) {
            float moveX = input.getMousePos().getX() - window.getWidth() / 2;
            float moveY = input.getMousePos().getY() - window.getHeight() / 2;
            float rotateX = 2 * rotateSpeed * (moveY / (float) window.getHeight()) * (fovAngle / 2.0f);
            float rotateY = 2 * rotateSpeed * (moveX / (float) window.getWidth()) * (fovAngle / 2.0f);
            if (!(camera.getForward().getY() >= 0.95f && moveY < 0) &&
                !(camera.getForward().getY() <= -0.95f && moveY > 0)) {
                camera.rotateX(-rotateX);
            }
            camera.rotateY(rotateY);
            input.setMousePos(window.getWidth() / 2, window.getHeight() / 2);
        }
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
        camera.move(-1.0f * camera.getForward(), moveSpeed);
    }
    if(input.getKeyState(ESCAPE_KEY)) {
        glutLeaveMainLoop();
    }
}
