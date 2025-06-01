#include "player.hpp"


namespace sms {

Degree Player::getDirection()
{
return m_direction.getDegrees();
}
raylib::Rectangle Player::getRectangle() {
    return m_rectangle;
}
void Player::setDirection(Degree direction) {
    m_direction.setDegrees(direction);
}
void Player::increaseSpeed() {
    if (m_speed <= m_maxSpeed)
        m_speed += m_acceleration;
    else m_speed = m_maxSpeed;
}
void Player::decreaseSpeed() {
    if (m_speed >= -(m_maxSpeed))
        m_speed -= m_acceleration;
    else m_speed = -(m_maxSpeed);

}
raylib::Vector2 Player::getVector() {
    return Vector2{static_cast<float>(m_speed * cos(m_direction.getRadians())),
    	       static_cast<float>(m_speed * sin(m_direction.getRadians()))};
}
void Player::rotate(Degree degree) {
    setDirection(m_direction.getDegrees().getDegrees() + degree.getDegrees());
}
void Player::draw() {
    m_rectangle.Draw(m_rectangle.GetSize() * 1/2.0, m_direction.getDegrees().getDegrees(), RED);
}

} // namespace sms
