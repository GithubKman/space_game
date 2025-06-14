#ifndef TEXTURE_CACHE_HPP
#define TEXTURE_CACHE_HPP

#include <memory>
#include <string>
#include <unordered_map>

#include "raylib-cpp.hpp" // IWYU pragma: export
namespace sms {

class TextureCache {
public:
    raylib::Texture2D& load(const std::string& path) {
	auto it = textureCache.find(path);
	if (it != textureCache.end()) return *it->second;

	raylib::Texture2D tex {LoadTexture(path.c_str())};
	textureCache[path] = std::shared_ptr<raylib::Texture2D>(new raylib::Texture2D(std::move(tex)));
	return *textureCache[path];
    }

    void unloadAll() {
        for (auto& [_, tex] : textureCache) {
            tex -> Unload();
        }
        textureCache.clear();
    }
    int getSize() {
	return textureCache.size();
    }

private:
    std::unordered_map<std::string, std::shared_ptr<raylib::Texture2D>> textureCache;
};

} // namespace sms
#endif
