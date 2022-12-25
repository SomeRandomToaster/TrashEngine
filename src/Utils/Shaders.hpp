//
// Created by leo on 29/10/22.
//

#ifndef TRASHENGINE_RESOURCELOADER_HPP
#define TRASHENGINE_RESOURCELOADER_HPP

#endif //TRASHENGINE_RESOURCELOADER_HPP

class Shader {
    GLuint vShaderId;
    GLuint fShaderId;
    GLuint programId;
    GLuint compileShader(const std::string& filePath, const GLenum shaderType);
    GLuint linkProgram(GLuint vShader, GLuint fShader);
    map<string, GLint> uniformIdMap;
public:
    void initUniforms();
    void loadVertexShader(const std::string& filePath);
    void loadFragmentShader(const std::string& filePath);
    void compileShaderProgram();
    GLuint getProgramId();
    void addUniform(const string& name);
    void setUniform(const string& name, const int val);
    void setUniform(const string& name, const float val);
    void setUniform(const string& name, const vector3f& val);
    void setUniform(const string& name, const matrix4f& val);
};
class BasicShader : public Shader {
    const string BASIC_VERTEX_SHADER_PATH="../res/shaders/BasicVertexShader.glsl";
    const string BASIC_FRAGMENT_SHADER_PATH="../res/shaders/BasicFragmentShader.glsl";
public:
    BasicShader();
    void updateUniforms(const matrix4f& transformMatrix, const vector3f& color);
};
void Shader::initUniforms() {
    addUniform("transformMatrix");
    addUniform("color");
}
void Shader::loadVertexShader(const std::string& filePath) {
    vShaderId=compileShader(filePath, GL_VERTEX_SHADER);
}
void Shader::loadFragmentShader(const std::string& filePath) {
    fShaderId=compileShader(filePath, GL_FRAGMENT_SHADER);
}
void Shader::compileShaderProgram() {
    programId=linkProgram(vShaderId, fShaderId);
    glUseProgram(programId);
}
GLuint Shader::compileShader(const std::string& filePath, const GLenum shaderType) {
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
GLuint Shader::linkProgram(GLuint vShader, GLuint fShader) {
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
GLuint Shader::getProgramId() {
    return programId;
}
void Shader::addUniform(const std::string& name) {
    GLint uniformId=glGetUniformLocation(programId, name.c_str());
    uniformIdMap.insert({name, uniformId});
}
void Shader::setUniform(const string& name, const int val) {
    glUniform1i(uniformIdMap[name], val);
}
void Shader::setUniform(const string& name, const float val) {
    glUniform1f(uniformIdMap[name], val);
}
void Shader::setUniform(const string& name, const vector3f& val) {
    glUniform3f(uniformIdMap[name], val.getX(), val.getY(), val.getZ());
}
void Shader::setUniform(const string& name, const matrix4f& val) {
    glUniformMatrix4fv(uniformIdMap[name], 1, GL_FALSE, val.data);
}

BasicShader::BasicShader() {
    loadVertexShader(BASIC_VERTEX_SHADER_PATH);
    loadFragmentShader(BASIC_FRAGMENT_SHADER_PATH);
    compileShaderProgram();
    initUniforms();
}
void BasicShader::updateUniforms(const matrix4f& transformMatrix, const vector3f& color) {
    setUniform("transformMatrix", transformMatrix);
    setUniform("color", color);
}