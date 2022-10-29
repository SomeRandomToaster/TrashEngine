//
// Created by leo on 22/10/22.
//

#ifndef TRASHENGINE_MESH_HPP
#define TRASHENGINE_MESH_HPP

#endif //TRASHENGINE_MESH_HPP

class Mesh {
    //const string VERTEX_SHADER_PATH="../src/Graphics/Shaders/VertexShader.glsl";
    //const string FRAGMENT_SHADER_PATH="../src/Graphics/Shaders/FragmentShader.glsl";
    GLuint vboId;
    GLuint vShaderId;
    GLuint fShaderId;
    GLuint programId;
    GLuint compileShader(const string& filePath, const GLenum shaderType);
    GLuint linkProgram(GLuint vShader, GLuint fShader);
    int vCount;
public:
    void setProgramID(const GLuint program);
    void addVertices(const vector <Vertex> &v );
    void draw();
};
void Mesh::addVertices(const vector <Vertex> &v ) {

    vCount=v.size();
    GLfloat* vertices=new GLfloat[v.size()*3];
    for(int i=0; i<v.size(); i++) {
        vertices[i*3]=v[i].getPos().getX();
        vertices[i*3+1]=v[i].getPos().getY();
        vertices[i*3+2]=v[i].getPos().getZ();
    }
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, vCount*3*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    GLuint posAttributePosition = glGetAttribLocation(programId, "position");

    GLuint vaoId;
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glVertexAttribPointer(posAttributePosition, vCount, GL_FLOAT, false, 0, nullptr);
    glEnableVertexAttribArray(posAttributePosition);

}
void Mesh::draw() {
    glDrawArrays(GL_TRIANGLES, 0, vCount);
    //cout << "draw" << endl;
}
GLuint Mesh::compileShader(const string& filePath, const GLenum shaderType) {
    GLuint shaderID = glCreateShader(shaderType);
    string shaderCode;
    ifstream shaderFile(filePath);
    if(shaderFile.is_open()) {
        stringstream shaderCodeStream;
        shaderCodeStream << shaderFile.rdbuf();
        shaderCode=shaderCodeStream.str();
        shaderFile.close();
    }
    else {
        cerr << "Error opening shaderFile for ";
        if(shaderType==GL_FRAGMENT_SHADER) {
            cerr << "fragment";
        }
        if(shaderType==GL_VERTEX_SHADER) {
            cerr << "vertex";
        }
        cerr << " shader" << endl;
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
GLuint Mesh::linkProgram(GLuint vShader, GLuint fShader) {
    GLuint programID=glCreateProgram();
    if (programID == 0)
    {
        cout << "Error Creating Shader Program";
        return 0;
    }
    glAttachShader(programID, vShader);
    glAttachShader(programID, fShader);
    glLinkProgram(programID);

    GLint linkStatus;
    glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);

    if (!linkStatus) { // If the linking failed
        cout << "Error Linking program";
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
void Mesh::setProgramID(const GLuint program) {
    programId=program;
}