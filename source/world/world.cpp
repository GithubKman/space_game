#include "world.hpp"
#include "chunk/chunk.hpp"
#include "chunk/chunk_coordinate.hpp"
#include "chunk/chunk_map.hpp"

namespace sms {

void World::update() {
    for (auto& pair : m_chunkMap.getChunks(m_worldLoc.getChunk(), m_entities)) {
	pair.second.get().clearEntities();
    }
    for (Entity& entity : m_entities) {
	entity.update();
	for (auto& pair : m_chunkMap.getChunks(m_worldLoc.getChunk(), m_entities)) {
	    if (entity.getCoordinate().getChunk() == pair.second.get().getCoordinate()) {
		pair.second.get().addEntity(entity);
	    }
	}
    }

}
void World::draw(ChunkCoordinate worldLoc) {
    m_chunkMap.draw(worldLoc, m_entities);
}

} // namespace sms
