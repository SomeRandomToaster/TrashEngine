//
// Created by leo on 13/10/22.
//

#ifndef TRASHENGINE_VECTORS_HPP
#define TRASHENGINE_VECTORS_HPP

#endif //TRASHENGINE_VECTORS_HPP

class vector2f {
    double x, y;
public:
    vector2f(const double x, const double y);
    void setX(const double x);
    void setY(const double y);
    double getX() const;
    double getY() const;
    double length() const;
    vector2f normalize() const;
    vector2f rotate(const double angle) const;
    vector2f operator+ (const vector2f& v) const;
    vector2f operator- (const vector2f& v) const;
    vector2f operator/ (const double a) const;
    friend ostream& operator<< (ostream &out, const vector2f& v);
    friend vector2f operator* (const double a, const vector2f& v);
    friend vector2f operator* (const vector2f& v, const double a);
    friend double dot(const vector2f& v, const vector2f& w);
};

class vector3f {
    double x, y, z;
public:
    vector3f(const double x, const double y, const double z);
    void setX(const double x);
    void setY(const double y);
    void setZ(const double z);
    double getX() const;
    double getY() const;
    double getZ() const;
    double length() const;
    vector3f normalize() const;
    vector3f operator+ (const vector3f& v) const;
    vector3f operator- (const vector3f& v) const;
    vector3f operator/ (const double a) const;
    friend ostream& operator<< (ostream &out, const vector3f& v);
    friend vector3f operator* (const double a, const vector3f& v);
    friend vector3f operator* (const vector3f& v, const double a);
    friend double dot(const vector3f& v, const vector3f& w);
    friend vector3f cross(const vector3f& v, const vector3f& w);
};

vector2f::vector2f(const double x, const double y) {
    this->x=x;
    this->y=y;
}
ostream& operator<< (ostream &out, const vector2f& v) {
    out << "X: " << v.x << "  Y: " << v.y;
    return out;
}
void vector2f::setX(const double x) {
    this->x=x;
}
void vector2f::setY(const double y) {
    this->y=y;
}
double vector2f::getX() const {
    return x;
}
double vector2f::getY() const {
    return y;
}
double vector2f::length() const {
    return sqrt(x*x+y*y);
}
vector2f vector2f::normalize() const {
    double len=this->length();
    return vector2f(x/len, y/len);
}
vector2f vector2f::rotate(const double angle) const {
    double new_x=x*cos(angle)-y*sin(angle);
    double new_y=x*sin(angle)+y*cos(angle);
    return vector2f(new_x, new_y);
}
vector2f vector2f::operator+ (const vector2f& v) const {
    return vector2f(x+v.x, y+v.y);
}
vector2f vector2f::operator- (const vector2f& v) const {
    return vector2f(x-v.x, y-v.y);
}
vector2f vector2f::operator/ (const double a) const {
    return vector2f(x/a, y/a);
}
vector2f operator* (const double a, const vector2f& v) {
    return vector2f(v.x*a, v.y*a);
}
vector2f operator* (const vector2f& v, const double a) {
    return vector2f(v.x*a, v.y*a);
}
double dot(const vector2f& v, const vector2f& w) {
    return v.x*w.x+v.y*w.y;
}

vector3f::vector3f(const double x, const double y, const double z) {
    this->x=x;
    this->y=y;
    this->z=z;
}
void vector3f::setX(const double x) {
    this->x=x;
}
void vector3f::setY(const double y) {
    this->y=y;
}
void vector3f::setZ(const double z) {
    this->z=z;
}
double vector3f::getX() const {
    return x;
}
double vector3f::getY() const {
    return y;
}
double vector3f::getZ() const {
    return z;
}
double vector3f::length() const {
    return sqrt(x*x+y*y+z*z);
}
vector3f vector3f::normalize() const {
    double len=this->length();
    return vector3f(x/len, y/len, z/len);
}
vector3f vector3f::operator+ (const vector3f& v) const {
    return vector3f(x+v.x, y+v.y, z+v.z);
}
vector3f vector3f::operator- (const vector3f& v) const {
    return vector3f(x-v.x, y-v.y, z-v.z);
}
vector3f vector3f::operator/ (const double a) const {
    return vector3f(x/a, y/a, z/a);
}
ostream& operator<< (ostream &out, const vector3f& v) {
    out << "X: " << v.x << " Y: " << v.y << " Z: " << v.z;
    return out;
}
vector3f operator* (const double a, const vector3f& v) {
    return vector3f(v.x*a, v.y*a, v.z*a);
}
vector3f operator* (const vector3f& v, const double a) {
    return vector3f(v.x*a, v.y*a, v.z*a);
}
double dot(const vector3f& v, const vector3f& w) {
    return v.x*w.x+v.y*w.y+v.z*w.z;
}
vector3f cross(const vector3f& v, const vector3f& w) {
    double ans_x=v.y*w.z-v.z*w.y;
    double ans_y=v.x*w.z-v.z*w.x;
    double ans_z=v.x*w.y-v.y*w.x;
    return vector3f(ans_x, ans_y, ans_z);
}