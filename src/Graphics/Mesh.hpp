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
    GLuint vaoId;
    GLuint iboId;
    int iCount;
    int vCount;
    GLuint programId;
    //GLuint compileShader(const string& filePath, const GLenum shaderType);
    //GLuint linkProgram(GLuint vShader, GLuint fShader);
    GLuint* indices;
public:
    Mesh();
    void setProgramID(const GLuint program);
    void addVertices(const vector <Vertex> &v, const vector<GLuint> &i);
    void draw();
};
Mesh::Mesh() {
    vCount=0;
    iCount=0;
    glGenBuffers(1, &vboId);
    glGenBuffers(1, &iboId);

    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);
}
void Mesh::addVertices(const vector <Vertex> &vBuf, const vector<GLuint> &iBuf) {

    vCount=vBuf.size();
    iCount=iBuf.size();
    GLfloat* vertices=new GLfloat[vCount*3];
    for(int i=0; i<vCount; i++) {
        vertices[i*3]=vBuf[i].getPos().getX();
        vertices[i*3+1]=vBuf[i].getPos().getY();
        vertices[i*3+2]=vBuf[i].getPos().getZ();
    }
    indices=new GLuint[iCount];
    for(int i=0; i<iCount; i++) {
        indices[i]=iBuf[i];
    }
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, vCount*3*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iCount*sizeof(GLuint), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Mesh::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glVertexAttribPointer(glGetAttribLocation(programId, "position"), 3, GL_FLOAT, false, 0, nullptr);
    glEnableVertexAttribArray(glGetAttribLocation(programId, "position"));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glDrawElements(GL_TRIANGLES, iCount, GL_UNSIGNED_INT, nullptr);
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, vCount);

    glDisableVertexAttribArray(glGetAttribLocation(programId, "position"));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //cout << "draw" << endl;
}
/*GLuint Mesh::compileShader(const string& filePath, const GLenum shaderType) {
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
    }*//*

    return programID;
} */
void Mesh::setProgramID(const GLuint program) {
    programId=program;
}