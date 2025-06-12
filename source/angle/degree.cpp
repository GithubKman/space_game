#include "degree.hpp"
#include "Vector2.hpp"
#include "angle/radian.hpp"

namespace sms {

double Degree::getDegrees() const { return degrees; }
void Degree::setDegrees(double deg) { degrees = normalizeDegrees(deg); }

double Degree::getRadians() const { return degrees * M_PI / 180.0; }
void Degree::setRadians(double rad) { degrees = normalizeDegrees(rad * 180.0 / M_PI); }

raylib::Vector2 Degree::getVector2(float magnitude) {
    float radians = Radian {Degree {degrees}}.getRadians();
    Vector2 result;
    result.x = magnitude * std::cos(radians);
    result.y = magnitude * std::sin(radians);
    return result;
}

Degree Degree::multiplyDegrees(const Degree& degree) {
    return degrees * degree.getDegrees();
}

void Degree::addDegrees(const Degree& degree) {
    degrees += degree.getDegrees();
}
} // namespace sms
