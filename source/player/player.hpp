#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "angle/degree.hpp"
#include "angle/radian.hpp"
#include "raylib-cpp.hpp" // IWYU pragma: export

namespace sms {

class Player 
{
private:
    double m_speed;
    double m_maxSpeed;
    double m_acceleration;
    Radian m_direction;
    raylib::Rectangle m_rectangle;
public:
    Player(double speed, double maxSpeed, double acceleration, Degree direction) : m_speed {speed},
					     m_maxSpeed {maxSpeed},
					     m_direction {direction},
					     m_acceleration {acceleration},
					     m_rectangle {raylib::Vector2 {0, 0}, 
							  raylib::Vector2 {50, 25}}
    {}

    Degree getDirection();
    raylib::Rectangle getRectangle();
    void setDirection(Degree direction);
    void increaseSpeed();
    void decreaseSpeed();
    raylib::Vector2 getVector();
    void rotate(Degree degree);
    void draw();
    };

} // namespace sms

#endif
