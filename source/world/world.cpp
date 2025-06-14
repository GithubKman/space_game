#include "world.hpp"
#include "chunk/chunk.hpp"
#include "chunk/chunk_coordinate.hpp"
#include "chunk/chunk_map.hpp"

namespace sms {

void World::update(ChunkCoordinate worldLoc) {
    for (auto& pair : m_chunkMap.getChunks(worldLoc.getChunk(), m_entities, m_textureCache)) {
	pair.second.get().clearEntities();
    }
    for (Entity& entity : m_entities) {
	entity.update();
	for (auto& pair : m_chunkMap.getChunks(worldLoc.getChunk(), m_entities, m_textureCache)) {
	    if (entity.getCoordinate().getChunk() == pair.second.get().getCoordinate()) {
		pair.second.get().addEntity(entity);
	    }
	}
    }

}
void World::draw(ChunkCoordinate worldLoc) {
    m_chunkMap.draw(worldLoc, m_entities, m_textureCache);
}

} // namespace sms
