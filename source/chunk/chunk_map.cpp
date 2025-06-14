#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <functional>
#include <random>
#include <algorithm>

#include "chunk_map.hpp"
#include "angle/degree.hpp"
#include "chunk_coordinate.hpp"
#include "object/entity.hpp"
#include "object/texturecache.hpp"
#include "raylib.h"
#include "vector/vector2l.hpp"
namespace sms {

double getClampedNormal(double mean, double stddev, double min, double max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::normal_distribution<double> dist(mean, stddev);

    double value = dist(gen);
    return std::clamp(value, min, max);
}

void drawChunk(const std::unordered_map<Vector2i,
	       std::reference_wrapper<Chunk>> chunkMap,
	       const Vector2i& coordinate,
	       const Vector2l& offset)
{
    try {
	chunkMap
	    .at(coordinate)
	    .get()
	    .draw((Vector2l{coordinate} * static_cast<double>(g_chunkSize))+ offset);
    }
    catch (const std::out_of_range& e){
	std::cerr << "Chunk does not exist - " << e.what() << std::endl;
    }

}

void ChunkMap::drawChunks(const std::unordered_map<Vector2i,
			  std::reference_wrapper<Chunk>>& map,
			  const Vector2l& offset)
{
    for (const auto& pair : map) {
	drawChunk(map, pair.first, offset);
    }

}

std::unordered_map<Vector2i,
		   std::reference_wrapper<Chunk>>
ChunkMap::getChunks(
    const Vector2i& coordinate,
    std::vector<Entity>& entities,
    TextureCache& textureCache)
{
    std::unordered_map<Vector2i, std::reference_wrapper<Chunk>> localChunks;

    for (int x {-m_renderDistance}; x <= m_renderDistance; ++x) {
	for (int y {-m_renderDistance}; y <= m_renderDistance; ++y) {
	    Vector2i localPos {coordinate - Vector2i{x, y}};
	    if (!m_chunkMap.count(localPos)) {
		m_chunkMap.insert({localPos, localPos});
		if (GetRandomValue(1, 10) == 10) {
		    entities.push_back(
			Entity {
			    Degree {static_cast<double>(GetRandomValue(0, 359))}.getVector2(
			    static_cast<float>(GetRandomValue(1, 100))),
			ChunkCoordinate{
			    {static_cast<double>(GetRandomValue(0, 511)),
			     static_cast<double>(GetRandomValue(0, 511))},
				localPos
			    },
			static_cast<double>(GetRandomValue(0, 359)),
			getClampedNormal(0, 20, -359, 359),
			textureCache.load("resources/asteroid.png")

			
			});
		}
	    }
	    localChunks.insert({Vector2i{x, y}, m_chunkMap.at(localPos).getReference()});
	}
    }
    return localChunks;
}

void ChunkMap::draw(const ChunkCoordinate& chunkCoord,
		    std::vector<Entity>& entities,
		    TextureCache& textureCache)
{
    drawChunks(getChunks(chunkCoord.getChunk(),
			 entities,
			 textureCache),
	       chunkCoord.getLocal());
}

void ChunkMap::setRenderDistance(int renderDistance)
{
    m_renderDistance = renderDistance;
}
} // namespace sms
