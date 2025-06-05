#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <format>

#include "raylib-cpp.hpp" // IWYU pragma: export

#include "text_object.hpp"
#include "vector/vector2i.hpp"
#include "globals.hpp"
namespace sms {

class Chunk {
private:
    Vector2i m_coordinate;
    std::vector<TextObject> m_textObjects;
    inline static const raylib::Vector2 m_size {g_chunkSize - 1, g_chunkSize - 1};
public:
    Chunk(Vector2i coordinate) : m_coordinate {coordinate},
				 m_textObjects {{{256, 256}, std::format("Chunk [{}, {}]", m_coordinate.GetX(), m_coordinate.GetY())}} {}
    Chunk(const Chunk& chunk) : m_coordinate {chunk.m_coordinate}, m_textObjects {chunk.m_textObjects} {}
    Chunk() : m_coordinate {0, 0} {}

    Chunk& getReference() {
	return *this;
    }

    void draw(raylib::Vector2 offset) const {
	if (!m_textObjects.empty())
	for (TextObject element : m_textObjects) {
	    element.draw(offset);
	}
    }
    void operator=(const Chunk& chunk) {
	if (this != &chunk) {
	    *this = chunk;
	}
    }
};

} // namespace sms

#endif
