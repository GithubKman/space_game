#ifndef DEGREE_HPP
#define DEGREE_HPP

#include <cmath>

namespace sms {

class Degree {
private:
    double degrees;

    static double normalizeDegrees(double deg) {
        deg = std::fmod(deg, 360.0);
        return deg < 0 ? deg + 360.0 : deg;
    }

public:
    // Constructors
    Degree() : degrees(0.0) {}
    Degree(double deg) : degrees(normalizeDegrees(deg)) {}

    // Getter and Setter for Degrees
    double getDegrees() const;
    void setDegrees(double deg);

    // Getter and Setter for Radians
    double getRadians() const;
    void setRadians(double rad);
};

} // namespace sms

#endif
