#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "chunk/chunk_coordinate.hpp"
#include "chunk/chunk_map.hpp"
#include "object/entity.hpp"
#include "object/texturecache.hpp"

namespace sms {

class World {
private:
    ChunkMap m_chunkMap;
    std::vector<Entity> m_entities;
    TextureCache m_textureCache {};
public:
    World() : m_chunkMap(),
	      m_entities() {
    }
    void update(ChunkCoordinate worldLoc);

    void draw(ChunkCoordinate worldLoc);

    int getEntityCount() {
	return m_entities.size();
    }
    int getTextureCount() {
	return m_textureCache.getSize();
    }
};

} // namespace sms
#endif
