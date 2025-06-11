#include "degree.hpp"

namespace sms {

double Degree::getDegrees() const { return degrees; }
void Degree::setDegrees(double deg) { degrees = normalizeDegrees(deg); }

double Degree::getRadians() const { return degrees * M_PI / 180.0; }
void Degree::setRadians(double rad) { degrees = normalizeDegrees(rad * 180.0 / M_PI); }

Degree Degree::multiplyDegrees(const Degree& degree) {
    return degrees * degree.getDegrees();
}

void Degree::addDegrees(const Degree& degree) {
    degrees *= degree.getDegrees();
}
} // namespace sms
