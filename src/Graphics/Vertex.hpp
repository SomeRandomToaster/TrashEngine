//
// Created by leo on 22/10/22.
//

#ifndef TRASHENGINE_VERTEX_HPP
#define TRASHENGINE_VERTEX_HPP

#endif //TRASHENGINE_VERTEX_HPP

#define V_SIZE 8

class Vertex {
    vector3f pos;
    vector2f texCoord;
    vector3f normal;

public:
    Vertex(const vector3f& pos, const vector2f& texCoord, const vector3f& normal);
    vector3f getPos() const;
    vector2f getTexCoord() const;
    vector3f getNormal() const;
    void setPos(const vector3f& newPos);
    void setTexCoord(const vector2f& newTexCoord);
    void setNormal(const vector3f& newNormal);
};

Vertex::Vertex(const vector3f& pos, const vector2f& texCoord, const vector3f& normal=vector3f(0, 0, 0)):
    pos(pos),
    texCoord(texCoord), normal(normal)
    {}
vector3f Vertex::getPos() const {
    return pos;
}
vector2f Vertex::getTexCoord() const {
    return texCoord;
}
vector3f Vertex::getNormal() const {
    return normal;
}
void Vertex::setPos(const vector3f& newPos) {
    pos=newPos;
}
void Vertex::setTexCoord(const vector2f& newTexCoord) {
    texCoord=newTexCoord;
}
void Vertex::setNormal(const vector3f& newNormal) {
    normal=newNormal;
}