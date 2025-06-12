#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "chunk/chunk_coordinate.hpp"
#include "chunk/chunk_map.hpp"
#include "object/entity.hpp"

namespace sms {

class World {
private:
    ChunkCoordinate m_worldLoc;
    ChunkMap m_chunkMap;
    std::vector<Entity> m_entities;
public:
    World() : m_worldLoc {{0,0}, {0,0}},
	      m_chunkMap(),
	      m_entities() {
    }
    void update();

    void draw(ChunkCoordinate worldLoc);
};

} // namespace sms
#endif
