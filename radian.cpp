#include "radian.hpp"

namespace sms {

double Radian::getRadians() const { return radians; }
void Radian::setRadians(double rad) { radians = normalize(rad); }
Degree Radian::getDegrees() const {
    return Degree(radians * 180.0 / M_PI);
}

void Radian::setDegrees(Degree deg) {
    radians = normalize(deg.getDegrees() * M_PI / 180.0);
}

} // namespace sms

