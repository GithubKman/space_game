#include "entity.hpp"

#include <raylib.h>
#include <vector>
#include <cstddef>  // for std::byte

namespace sms {

std::vector<std::vector<std::byte>> ConvertImageToAlphaMask(const Image& image) {
    int width = image.width;
    int height = image.height;

    Color* pixels = LoadImageColors(image); // RGBA per pixel
    std::vector<std::vector<std::byte>> mask(height);

    for (int y = 0; y < height; ++y) {
        std::vector<std::byte> row;
        for (int x = 0; x < width; x += 8) {
            std::byte b{0};
            for (int bit = 0; bit < 8; ++bit) {
                int px = x + bit;
                if (px >= width) break;

                Color pixel = pixels[y * width + px];
                if (pixel.a > 127) {
                    b |= static_cast<std::byte>(1 << (7 - bit)); // MSB is leftmost pixel
                }
            }
            row.push_back(b);
        }
        mask[y] = std::move(row);
    }

    UnloadImageColors(pixels);
    return mask;
}
Image CreateDebugImageFromMask(const std::vector<std::vector<std::byte>>& mask, int width, int height) {
    Image debug = GenImageColor(width, height, BLACK); // Default black (transparent)
    Color* pixels = LoadImageColors(debug);

    for (int y = 0; y < height; ++y) {
        const auto& row = mask[y];
        for (size_t byteIndex = 0; byteIndex < row.size(); ++byteIndex) {
            std::byte b = row[byteIndex];
            for (int bit = 0; bit < 8; ++bit) {
                int x = byteIndex * 8 + bit;
                if (x >= width) break;

                bool isOpaque = (static_cast<unsigned char>(b) & (1 << (7 - bit))) != 0;
                if (isOpaque) {
                    pixels[y * width + x] = WHITE;
                }
            }
        }
    }

    Image result = GenImageColor(width, height, BLACK); // Create result image
    UpdateTextureRec(LoadTextureFromImage(debug), { 0, 0, (float)width, (float)height }, pixels);
    UnloadImage(debug);
    return result;
}

void Entity::update() {
    m_coordinate += m_movement * GetFrameTime();
    m_rotation += m_rotationPerSecond * Degree {GetFrameTime()};
}
void Entity::draw(Vector2l offset) const {
    m_texture.Draw(offset - m_coordinate.getLocal());
}

} // namespace sms
