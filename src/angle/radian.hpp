#ifndef RADIAN_HPP
#define RADIAN_HPP

#include "degree.hpp"
#include <cmath>

namespace sms {

class Radian {
private:
    double radians;
    constexpr static double TWO_PI {M_PI * 2};

    static double normalize(double rad) {
        rad = std::fmod(rad, TWO_PI);
        return rad < 0 ? rad + TWO_PI : rad;
    }

public:
    // Constructors
    Radian() : radians(0.0) {}
    explicit Radian(double rad) : radians {normalize(rad)} {}
    explicit Radian(const Degree& deg) : radians {normalize(deg.getRadians())} {}

    // Getter and Setter for Radians
    double getRadians() const;
    void setRadians(double rad);

    // Getter and Setter for Degrees
    Degree getDegrees() const;
    void setDegrees(Degree deg);
};

} // namespace sms

#endif
