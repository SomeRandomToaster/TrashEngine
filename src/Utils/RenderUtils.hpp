//
// Created by leo on 22/10/22.
//



#ifndef TRASHENGINE_RENDERUTILS_HPP
#define TRASHENGINE_RENDERUTILS_HPP

#endif //TRASHENGINE_RENDERUTILS_HPP

using namespace  std;

class RenderTool {
    const static int defaultVertexBufSize=10000;

    void createVertexArray();
public:
    GLuint programID;
    RenderTool();
    void clearScreen(double r=0, double g=0, double b=0);
    std::string getGlVersion();
};

RenderTool::RenderTool() {
    //createVertexArray();
    clearScreen();
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FRAMEBUFFER_SRGB);

}
void RenderTool::clearScreen(const double r, const double g, const double b) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(r, g, b, 0);
}
std::string RenderTool::getGlVersion() {
    return std::string((const char*)glGetString(GL_VERSION));
}
