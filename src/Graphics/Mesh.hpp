//
// Created by leo on 22/10/22.
//

#ifndef TRASHENGINE_MESH_HPP
#define TRASHENGINE_MESH_HPP

#endif //TRASHENGINE_MESH_HPP

class Mesh {
    GLuint vboId;
    GLuint vaoId;
    GLuint iboId;
    int iCount;
    int vCount;
    GLuint programId;
    GLuint* indices;
public:
    Mesh();
    void setProgramID(const GLuint program);
    void addVertices(const vector <Vertex> &v, const vector<GLuint> &i);
    void addVerticesFromModel(const string& fileName);
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

void Mesh::setProgramID(const GLuint program) {
    programId=program;
}
void Mesh::addVerticesFromModel(const string& fileName) {
    ifstream model;
    model.open(fileName);
    vector <string> strArray;
    while(!model.eof()) {
        string str;
        model >> str;
        strArray.push_back(str);
    }
    vector<Vertex> vBuf;
    vector<GLuint> iBuf;
    for(int i=0; i<strArray.size(); i++) {
        if(strArray[i].size()==1 && strArray[i][0]=='v') {
            float x = stof(strArray[i+1]);
            float y = stof(strArray[i+2]);
            float z = stof(strArray[i+3]);
            Vertex newVertex(vector3f(x, y, z));
            vBuf.push_back(newVertex);
        }
        if(strArray[i].size()==1 && strArray[i][0]=='f') {
            float p1 = stoi(strArray[i+1])-1;
            float p2 = stoi(strArray[i+2])-1;
            float p3 = stoi(strArray[i+3])-1;
            iBuf.push_back(p1);
            iBuf.push_back(p2);
            iBuf.push_back(p3);
        }
    }
    addVertices(vBuf, iBuf);
}