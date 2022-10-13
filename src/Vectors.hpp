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
    friend ostream& operator<< (ostream &out, const vector2f& v);
};

vector2f::vector2f(const double x, const double y) {
    this->x=x;
    this->y=y;
}
ostream& operator<< (ostream &out, const vector2f& v) {
    out << "X: " << v.x << "  Y: " << v.y;
    return out;
}
