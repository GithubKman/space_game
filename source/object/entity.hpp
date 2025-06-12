#ifndef OBJECT_ENTITY_HPP
#define OBJECT_ENTITY_HPP

#include <cstddef>
#include <vector>
#include "angle/degree.hpp"
#include "chunk/chunk_coordinate.hpp"
#include "raylib-cpp.hpp" // IWYU pragma: export
#include "Vector2.hpp"
namespace sms {

class Entity {
private:
    //Components
    raylib::Vector2 m_movement;
    ChunkCoordinate m_coordinate;
    Degree m_rotation;
    double m_rotationPerSecond;
    raylib::Image m_image;
    raylib::Texture2D m_texture;
    raylib::Rectangle m_imageRectangle;

    std::vector<std::vector<std::byte>> ConvertImageToAlphaMask(const Image& image);


public:
    Entity(raylib::Vector2 movement,
	   ChunkCoordinate coordinate,
	   Degree rotation,
	   double rotationPerSecond,
	   raylib::Image image) :
    m_movement {movement},
    m_coordinate {coordinate},
    m_rotation {rotation},
    m_rotationPerSecond {rotationPerSecond},
    m_image {image},
    m_texture {image.LoadTexture()},
    m_imageRectangle {image.GetAlphaBorder(0.5f)}
    {}
    
    //Systems
    void update();
    void draw(Vector2l offset) const;

    ChunkCoordinate getCoordinate() {
	return m_coordinate;
    }

};

} // namespace sms

#endif
