#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <functional>

#include "chunk_map.hpp"
#include "chunk_coordinate.hpp"
#include "vector/vector2l.hpp"
namespace sms {

void drawChunk(const std::unordered_map<Vector2i, std::reference_wrapper<Chunk>> chunkMap, const Vector2i& coordinate, const Vector2l& offset) {
    try {
	chunkMap.at(coordinate).get().draw((Vector2l{coordinate} * static_cast<double>(g_chunkSize))+ offset);
    }
    catch (const std::out_of_range& e){
	std::cerr << "Chunk does not exist - " << e.what() << std::endl;
    }

}

void ChunkMap::drawChunks(const std::unordered_map<Vector2i, std::reference_wrapper<Chunk>>& map, const Vector2l& offset) {
    for (const auto& pair : map) {
	drawChunk(map, pair.first, offset);
    }

}

std::unordered_map<Vector2i, std::reference_wrapper<Chunk>> ChunkMap::getChunks(const Vector2i& coordinate) {
    std::unordered_map<Vector2i, std::reference_wrapper<Chunk>> localChunks;

    for (int x {-m_renderDistance}; x <= m_renderDistance; ++x) {
	for (int y {-m_renderDistance}; y <= m_renderDistance; ++y) {
	    Vector2i localPos {coordinate - Vector2i{x, y}};
	    if (!m_chunkMap.count(localPos)) {
		m_chunkMap.insert({localPos, localPos});
	    }
	    localChunks.insert({Vector2i{x, y}, m_chunkMap.at(localPos).getReference()});
	}
    }
    return localChunks;
}

void ChunkMap::draw(const ChunkCoordinate& chunkCoord) {
    drawChunks(getChunks(chunkCoord.getChunk()), chunkCoord.getLocal());
}

void ChunkMap::setRenderDistance(int renderDistance) {
    m_renderDistance = renderDistance;
}
} // namespace sms
