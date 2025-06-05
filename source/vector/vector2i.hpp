#ifndef VECTOR2i_HPP
#define VECTOR2i_HPP

#include <functional>

namespace sms {

class Vector2i {
private:
    int m_x;
    int m_y;
public:
    Vector2i(int x) : m_x {x}, m_y {0} {}
    Vector2i(int x, int y) : m_x {x}, m_y {y} {}
    Vector2i(const Vector2i& vector) : m_x {vector.m_x}, m_y {vector.m_y} {}
    Vector2i() {}

    void SetX(int x) {
	m_x = x;
    }
    void SetY(int y) {
	m_x = y;
    }

    double GetX() const{
	return m_x;
    }
    double GetY() const{
	return m_y;
    }
    void Add(const Vector2i& vector) {
	m_x += vector.m_x;
	m_y += vector.m_y;
    }
    void Subtract(const Vector2i& vector) {
	m_x -= vector.m_x;
	m_y -= vector.m_y;
    }
    bool IsEqual(const Vector2i& vector) const {
	return m_x == vector.m_x && m_y == vector.m_y;
    }
    void ChangeX(int increment) {
	m_x += increment;
    }
    void ChangeY(int increment) {
	m_y += increment;
    }

    Vector2i operator + (const Vector2i& vector) const {
	return {m_x + vector.m_x, m_y + vector.m_y};
    }
    Vector2i operator - (const Vector2i& vector) const {
	return {m_x - vector.m_x, m_y - vector.m_y};
    }
    void operator += (const Vector2i& vector) {
	Add(vector);
    }
    bool operator==(const Vector2i& vector) const {
        return IsEqual(vector);
    }
};

} // namespace sms

namespace std {
    template<>
    struct hash<sms::Vector2i> {
        size_t operator()(const sms::Vector2i& v) const {
            size_t h1 = hash<int>{}(v.GetX());
            size_t h2 = hash<int>{}(v.GetY());
            return h1 ^ (h2 << 1); // or use boost::hash_combine style
        }
    };
}

#endif
