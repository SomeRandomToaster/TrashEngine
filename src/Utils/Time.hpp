//
// Created by leo on 09/10/22.
//

#ifndef TRASHENGINE_TIME_HPP
#define TRASHENGINE_TIME_HPP

#endif //TRASHENGINE_TIME_HPP

class TimeClass {
    double delta;
public:
    const double SECOND = 1e9;
    void setDelta(const double delta);
    double getDelta();
    unsigned long long getTime();
};

void TimeClass::setDelta(const double delta) {
    this->delta=delta;
}
double TimeClass::getDelta() {
    return delta;
}
unsigned long long TimeClass::getTime() {
    using namespace std::chrono;
    return duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
}