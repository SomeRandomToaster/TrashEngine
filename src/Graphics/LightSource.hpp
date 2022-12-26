//
// Created by leo on 26/12/22.
//

#ifndef TRASHENGINE_LIGHTSOURCE_HPP
#define TRASHENGINE_LIGHTSOURCE_HPP

#endif //TRASHENGINE_LIGHTSOURCE_HPP

class LightSource {
    vector3f pos;
    vector3f color;
public:
    LightSource(const vector3f& pos=vector3f(0, 0, 0), const vector3f& color=vector3f(0, 0, 0));
    void setPos(const vector3f& newPos);
    vector3f getPos() const;
    void setColor(const vector3f& newColor);
    vector3f getColor() const;
};
LightSource::LightSource(const vector3f& pos, const vector3f& color) :
    pos(pos),
    color(color)
{}
void LightSource::setPos(const vector3f& newPos) {
    pos=newPos;
}
vector3f LightSource::getPos() const {
    return pos;
}
void LightSource::setColor(const vector3f& newColor) {
    color=newColor;
}
vector3f LightSource::getColor() const {
    return color;
}