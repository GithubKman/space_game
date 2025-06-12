#ifndef VECTOR2L_HPP
#define VECTOR2L_HPP

#include "raylib-cpp.hpp" // IWYU pragma: export

#include "vector2i.hpp"

namespace sms {

class Vector2l {
private:
    double m_x;
    double m_y;
public:
    Vector2l(double x) : m_x {x}, m_y {0.0} {}
    Vector2l(double x, double y) : m_x {x}, m_y {y} {}
    Vector2l(const Vector2l& vector) : m_x {vector.m_x}, m_y {vector.m_y} {}
    Vector2l(const raylib::Vector2& vector) : m_x {vector.GetX()}, m_y {vector.GetY()} {}
    Vector2l(const Vector2i& vector) : m_x {vector.GetX()}, m_y {vector.GetY()} {}

    void SetX(double x) {
	m_x = x;
    }
    void SetY(double y) {
	m_x = y;
    }

    double GetX() const{
	return m_x;
    }
    double GetY() const{
	return m_y;
    }
    raylib::Vector2 GetVector2() {
	return raylib::Vector2 {static_cast<float>(m_x), static_cast<float>(m_y)};
    }
    void Add(const Vector2l& vector) {
	m_x += vector.m_x;
	m_y += vector.m_y;
    }
    Vector2l Scaled(double scalar) {
	return {m_x * scalar, m_y * scalar};
    }
    bool IsEqual(const Vector2l& vector) const {
	return m_x == vector.m_x && m_y == vector.m_y;
    }
    operator raylib::Vector2() const {
	return {static_cast<float>(m_x), static_cast<float>(m_y)};
    }
    void ChangeX(double increment) {
	m_x += increment;
    }
    void ChangeY(double increment) {
	m_y += increment;
    }

    Vector2l operator + (const Vector2l& vector) const {
	return {m_x + vector.m_x, m_y + vector.m_y};
    }
    Vector2l operator-(const Vector2l& vector) const {
	return {m_x - vector.m_x, m_y - vector.m_y};
    }
    Vector2l operator*(double scalar) {
	return Scaled(scalar);
    }
    void operator += (const Vector2l& vector) {
	Add(vector);
    }
    bool operator==(const Vector2l& vector) const {
	return IsEqual(vector);
    }
};

} // namespace sms

#endif
