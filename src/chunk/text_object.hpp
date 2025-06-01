#ifndef TEXT_OBJECT_HPP
#define TEXT_OBJECT_HPP

#include "raylib-cpp.hpp" // IWYU pragma: export

namespace sms {

struct TextObject {
    raylib::Vector2 coordinate;
    raylib::Text text;

    void draw(raylib::Vector2 offset) {
	text.Draw(offset - coordinate);
    }
};

} // namespace sms

#endif
