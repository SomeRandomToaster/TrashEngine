//
// Created by leo on 24/11/22.
//

#ifndef TRASHENGINE_CAMERA_HPP
#define TRASHENGINE_CAMERA_HPP

#endif //TRASHENGINE_CAMERA_HPP

class Camera {
    vector3f pos, forward, up;
public:
    Camera();
    Camera(const vector3f& pos, const vector3f& forward, const vector3f& up);
    vector3f getPos() const;
    vector3f getForward() const;
    vector3f getUp() const;
    vector3f getRight() const;
    vector3f getLeft() const;
    void setPos(const vector3f& pos);
    void setForward(const vector3f& forward);
    void setUp(const vector3f& up);
    void move(vector3f direction, float amount);
    void rotateX(const float& angle);
    void rotateY(const float& angle);
    void rotateZ(const float& angle);
};
Camera::Camera() :
    pos(vector3f(0, 0, 0)),
    forward(vector3f(1, 0, 0)),
    up(vector3f(0, 0, 1))
{}
Camera::Camera(const vector3f& pos, const vector3f& forward, const vector3f& up) :
    pos(pos),
    forward(forward),
    up(up)
{}

vector3f Camera::getPos() const {
    return pos;
}
vector3f Camera::getForward() const {
    return forward;
}
vector3f Camera::getUp() const {
    return up;
}
vector3f Camera::getRight() const {
    return cross(forward, up);
}
vector3f Camera::getLeft() const {
    return cross(up, forward);
}
void Camera::setPos(const vector3f& pos) {
    this->pos=pos;
}
void Camera::setForward(const vector3f& forward) {
    this->forward=forward;
}
void Camera::setUp(const vector3f& up) {
    this->up=up;
}
void Camera::move(vector3f direction, float amount) {
    pos=pos+direction.normalize()*amount;
}
void Camera::rotateX(const float& angle) {
    vector3f hAxis=cross(vector3f(0, 1, 0),forward);
    hAxis.normalize();
    forward=rotate(forward, hAxis, angle);
    forward=forward.normalize();
    up=cross(forward, hAxis);

}
void Camera::rotateY(const float& angle) {
    forward=rotate(forward, up, angle);
    up=up.normalize();
    forward=forward.normalize();
}
void Camera::rotateZ(const float& angle) {
    up=rotate(up, forward, angle);
    up=up.normalize();
    forward=forward.normalize();
}