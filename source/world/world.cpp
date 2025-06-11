#include "world.hpp"
#include "chunk/chunk.hpp"
#include "chunk/chunk_map.hpp"

namespace sms {

void World::update(raylib::Vector2) {
    for (auto& pair : m_chunkMap.getChunks(m_worldLoc.getChunk())) {
	pair.second.get().clearEntities();
    }
    for (Entity& entity : m_entities) {
	entity.update();
	for (auto& pair : m_chunkMap.getChunks(m_worldLoc.getChunk())) {
	    if (entity.getCoordinate().getChunk() == pair.second.get().getCoordinate()) {
		pair.second.get().addEntity(entity);
	    }
	}
    }

}

} // namespace sms
