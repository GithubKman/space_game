#ifndef OBJECT_ENTITY_HPP
#define OBJECT_ENTITY_HPP

#include "chunk/chunk_coordinate.hpp"
#include "player/player.hpp"
#include "raylib-cpp.hpp"
#include "Vector2.hpp"
namespace sms {

class Entity {
private:
    //Components
    raylib::Vector2 movement;
    ChunkCoordinate m_coordinate;

public:
    //Systems
};

} // namespace sms

#endif
