#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <format>
#include <functional>
#include <vector>

#include "raylib-cpp.hpp" // IWYU pragma: export

#include "text_object.hpp"
#include "vector/vector2i.hpp"
#include "object/entity.hpp"
#include "globals.hpp"
namespace sms {

class Chunk {
private:
    Vector2i m_coordinate;
    std::vector<TextObject> m_textObjects;
    std::vector<std::reference_wrapper<Entity>> m_entities;
    inline static const raylib::Vector2 m_size {g_chunkSize - 1, g_chunkSize - 1};
public:
    Chunk(Vector2i coordinate) : m_coordinate {coordinate},
				 m_textObjects {{{256, 256}, std::format("Chunk [{}, {}]", m_coordinate.GetX(), m_coordinate.GetY())}} {}
    Chunk(const Chunk& chunk) : m_coordinate {chunk.m_coordinate}, m_textObjects {chunk.m_textObjects} {}
    Chunk() : m_coordinate {0, 0} {}

    Chunk& getReference() {
	return *this;
    }
    Vector2i getCoordinate() {
	return m_coordinate;
    }
    void clearEntities() {
	m_entities.clear();
    }
    void addEntity(Entity& entity) {
	m_entities.push_back(entity);
    }

    void draw(raylib::Vector2 offset) {
	if (!m_textObjects.empty()) {
	    for (TextObject element : m_textObjects) {
		element.draw(offset);
	    }
	}
	if (!m_entities.empty()) {
	    for (const Entity& element : m_entities) {
		element.draw(offset);
	    }
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
