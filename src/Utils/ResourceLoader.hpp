//
// Created by leo on 29/10/22.
//

#ifndef TRASHENGINE_RESOURCELOADER_HPP
#define TRASHENGINE_RESOURCELOADER_HPP

#endif //TRASHENGINE_RESOURCELOADER_HPP

class ResourceLoader {
    GLuint vShaderId;
    GLuint fShaderId;
    GLuint programId;
    GLuint compileShader(const std::string& filePath, const GLenum shaderType);
    GLuint linkProgram(GLuint vShader, GLuint fShader);
public:
    void loadVertexShader(const std::string& filePath);
    void loadFragmentShader(const std::string& filePath);
    void compileShaderProgram();
    GLuint getProgramID();
};

void ResourceLoader::loadVertexShader(const std::string& filePath) {
    vShaderId=compileShader(filePath, GL_VERTEX_SHADER);
}
void ResourceLoader::loadFragmentShader(const std::string& filePath) {
    fShaderId=compileShader(filePath, GL_FRAGMENT_SHADER);
}
void ResourceLoader::compileShaderProgram() {
    programId=linkProgram(vShaderId, fShaderId);
    glUseProgram(programId);
}
GLuint ResourceLoader::compileShader(const std::string& filePath, const GLenum shaderType) {
    GLuint shaderID = glCreateShader(shaderType);
    std::string shaderCode;
    std::ifstream shaderFile(filePath);
    if(shaderFile.is_open()) {
        std::stringstream shaderCodeStream;
        shaderCodeStream << shaderFile.rdbuf();
        shaderCode=shaderCodeStream.str();
        shaderFile.close();
    }
    else {
        std::cerr << "Error opening shaderFile for ";
        if(shaderType==GL_FRAGMENT_SHADER) {
            std::cerr << "fragment";
        }
        if(shaderType==GL_VERTEX_SHADER) {
            std::cerr << "vertex";
        }
        std::cerr << " shader" << std::endl;
    }
    GLint Result = GL_FALSE;
    int logLength;
    char const * shaderCodePointer = shaderCode.c_str();
    glShaderSource(shaderID, 1, &shaderCodePointer , NULL);
    glCompileShader(shaderID);

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
    if ( logLength > 0 ){
        std::vector<char> errorMessage(logLength+1);
        glGetShaderInfoLog(shaderID, logLength, NULL, &errorMessage[0]);
        fprintf(stdout, "%sn", &errorMessage[0]);
    }
    return shaderID;
}
GLuint ResourceLoader::linkProgram(GLuint vShader, GLuint fShader) {
    GLuint programID=glCreateProgram();
    if (programID == 0)
    {
        std::cerr << "Error Creating Shader Program";
        return 0;
    }
    glAttachShader(programID, vShader);
    glAttachShader(programID, fShader);
    glLinkProgram(programID);

    GLint linkStatus;
    glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);

    if (!linkStatus) { // If the linking failed
        std::cerr << "Error Linking program";
        glDetachShader(programID, vShader);
        glDetachShader(programID, fShader);
        glDeleteProgram(programID);

        return 0;
    }
    /*else {
        cout << "link successful" << endl;
    }*/

    return programID;
}
GLuint ResourceLoader::getProgramID() {
    return programId;
}