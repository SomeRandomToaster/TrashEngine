//
// Created by leo on 22/10/22.
//

#ifndef TRASHENGINE_VERTEX_HPP
#define TRASHENGINE_VERTEX_HPP

#endif //TRASHENGINE_VERTEX_HPP

class Vertex {
    vector3f pos;

public:
    const int SIZE=3;
    Vertex(const vector3f& pos);
    vector3f getPos() const;
    void setPos(const vector3f& newPos);
};

Vertex::Vertex(const vector3f& pos): pos(pos) {}
vector3f Vertex::getPos() const {
    return pos;
}
void Vertex::setPos(const vector3f& newPos) {
    pos=newPos;
}