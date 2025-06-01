#ifndef CHUNK_MAP_HPP
#define CHUNK_MAP_HPP

#include <unordered_map>

#include "raylib-cpp.hpp" // IWYU pragma: export

#include "globals.h"
#include "vector2i.hpp"
#include "vector2l.hpp"
#include "chunk.hpp"
#include "chunk-coordinate.hpp"

namespace sms {

class ChunkMap {
private:
    std::unordered_map<Vector2i, Chunk> m_chunkMap;
    static constexpr int m_defaultRenderDistance {2};
    int m_renderDistance;

    void fixInvariant() {
	if (m_renderDistance < 1) {
	    m_renderDistance = 1;
	}
	if (m_renderDistance > g_maxRenderDistance) {
	    m_renderDistance = g_maxRenderDistance;
	}
    }
public:
    ChunkMap() : m_chunkMap {}, m_renderDistance {m_defaultRenderDistance} {}
    ChunkMap(int renderDistance) : m_renderDistance {renderDistance}, m_chunkMap {} {}

    void genChunk(const Vector2i& coordinate);
    void drawChunks(const std::unordered_map<Vector2i, std::reference_wrapper<Chunk>>& map, const Vector2l& offset);
    std::unordered_map<Vector2i, std::reference_wrapper<Chunk>> getChunks(const Vector2i& coordinate);
    void draw(const ChunkCoordinate& chunkCoord);
    void setRenderDistance(int renderDistance);
};

} // namespace sms

#endif
