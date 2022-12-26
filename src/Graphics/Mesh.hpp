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
    void setProgramId(const GLuint program);
    void addVertices(vector <Vertex> &v, vector<GLuint> &i);
    void addVerticesFromModel(const string& fileName);
    void draw();
    void calcNormals(vector<Vertex>& vBuf, vector<GLuint>& iBuf);
};
Mesh::Mesh() {
    vCount=0;
    iCount=0;
    glGenBuffers(1, &vboId);
    glGenBuffers(1, &iboId);

    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);
}
void Mesh::addVertices(vector <Vertex> &vBuf, vector<GLuint> &iBuf) {
    calcNormals(vBuf, iBuf);
    vCount=vBuf.size();
    iCount=iBuf.size();
    GLfloat* vertices=new GLfloat[vCount*V_SIZE];
    for(int i=0; i<vCount; i++) {
        vertices[i*V_SIZE]=vBuf[i].getPos().getX();
        vertices[i*V_SIZE+1]=vBuf[i].getPos().getY();
        vertices[i*V_SIZE+2]=vBuf[i].getPos().getZ();
        vertices[i*V_SIZE+3]=vBuf[i].getTexCoord().getX();
        vertices[i*V_SIZE+4]=vBuf[i].getTexCoord().getY();
        vertices[i*V_SIZE+5]=vBuf[i].getNormal().getX();
        vertices[i*V_SIZE+6]=vBuf[i].getNormal().getY();
        vertices[i*V_SIZE+7]=vBuf[i].getNormal().getZ();
    }
    indices=new GLuint[iCount];
    for(int i=0; i<iCount; i++) {
        indices[i]=iBuf[i];
    }
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, vCount*V_SIZE*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iCount*sizeof(GLuint), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Mesh::draw() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, V_SIZE*sizeof(GLfloat), nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, V_SIZE*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, V_SIZE*sizeof(GLfloat), (void*)(5*sizeof(GLfloat)));
    //glVertexAttribPointer(glGetAttribLocation(programId, "position"), 3, GL_FLOAT, false, 5*sizeof(GLfloat), nullptr);

    glEnableVertexAttribArray(glGetAttribLocation(programId, "position"));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glDrawElements(GL_TRIANGLES, iCount, GL_UNSIGNED_INT, nullptr);
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, vCount);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //cout << "draw" << endl;
}

void Mesh::setProgramId(const GLuint program) {
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
            vector2f tmpTexCoord(0.5f, 0.8f);
            vector2f texCoord(x+0.5, z+0.5);
            Vertex newVertex(vector3f(x, y, z), texCoord);
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
void Mesh::calcNormals(vector<Vertex>& vBuf, vector<GLuint>& iBuf) {
    int fCount=iBuf.size()/3;
    for(int i=0; i<fCount; i++) {
        vector3f A=vBuf[iBuf[i*3]].getPos();
        vector3f B=vBuf[iBuf[i*3+1]].getPos();
        vector3f C=vBuf[iBuf[i*3+2]].getPos();
        vector3f BA=A-B;
        vector3f BC=C-B;
        vector3f normal=cross(BC, BA).normalize();
        vBuf[iBuf[i*3]].setNormal(normal+vBuf[iBuf[i*3]].getNormal());
        vBuf[iBuf[i*3+1]].setNormal(normal+vBuf[iBuf[i*3+1]].getNormal());
        vBuf[iBuf[i*3+2]].setNormal(normal+vBuf[iBuf[i*3+2]].getNormal());
    }
}