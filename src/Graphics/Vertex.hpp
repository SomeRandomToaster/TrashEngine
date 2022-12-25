//
// Created by leo on 22/10/22.
//

#ifndef TRASHENGINE_VERTEX_HPP
#define TRASHENGINE_VERTEX_HPP

#endif //TRASHENGINE_VERTEX_HPP

class Vertex {
    vector3f pos;
    vector2f texCoord;

public:
    const int SIZE=3;
    Vertex(const vector3f& pos, const vector2f& texCoord);
    vector3f getPos() const;
    vector2f getTexCoord() const;
    void setPos(const vector3f& newPos);
};

Vertex::Vertex(const vector3f& pos, const vector2f& texCoord): pos(pos), texCoord(texCoord) {}
vector3f Vertex::getPos() const {
    return pos;
}
vector2f Vertex::getTexCoord() const {
    return texCoord;
}
void Vertex::setPos(const vector3f& newPos) {
    pos=newPos;
}