#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "chunk/chunk_coordinate.hpp"
#include "chunk/chunk_map.hpp"
#include "object/entity.hpp"

namespace sms {

class World {
private:
    ChunkMap m_chunkMap;
    std::vector<Entity> m_entities;
public:
    World() : m_chunkMap(),
	      m_entities() {
    }
    void update(ChunkCoordinate worldLoc);

    void draw(ChunkCoordinate worldLoc);
};

} // namespace sms
#endif
