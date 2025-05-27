/*******************************************************************************************
*
*   raylib [core] example - Basic window (adapted for HTML5 platform)
*
*   This example is prepared to compile for PLATFORM_WEB and PLATFORM_DESKTOP
*   As you will notice, code structure is slightly different to the other examples...
*   To compile it for PLATFORM_WEB just uncomment #define PLATFORM_WEB at beginning
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib-cpp.hpp"
#include "raymath.hpp"
#include <cmath>
#include <vector>
#include <unordered_map>
#include <functional>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
const int screenWidth = 800;
const int screenHeight = 450;
const double FPS = 60.0;
//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------








class Degree;  // Forward declaration

constexpr double TWO_PI = 2.0 * M_PI;

constexpr int CHUNK_SIZE = 512; // 512 * 512



class Vector2i {
private:
    int m_x;
    int m_y;
public:
    Vector2i(int x) : m_x {x}, m_y {0} {}
    Vector2i(int x, int y) : m_x {x}, m_y {y} {}
    Vector2i(const Vector2i& vector) : m_x {vector.m_x}, m_y {vector.m_y} {}

    double GetX() {
	return m_x;
    }
    double GetY() {
	return m_y;
    }
    raylib::Vector2 GetVector2() {
	return raylib::Vector2 {static_cast<float>(m_x), static_cast<float>(m_y)};
    }
    void Add(const Vector2i& vector) {
	m_x += vector.m_x;
	m_y += vector.m_y;
    }
};
class ChunkCoord;
struct TextObject {
    Vector2 coordinate;
    raylib::Text text{"this is a chunk"};

    void draw(const ChunkCoord* chunk) {
	text.Draw(coordinate);
    }

};


struct Chunk {
    Vector2i coordinate;
    bool loaded;
    TextObject text;
    raylib::Vector2 size {CHUNK_SIZE - 1, CHUNK_SIZE - 1};
    };











class Vector2l {
private:
    double m_x;
    double m_y;
public:
    Vector2l(double x) : m_x {x}, m_y {0.0} {}
    Vector2l(double x, double y) : m_x {x}, m_y {y} {}
    Vector2l(const Vector2l& vector) : m_x {vector.m_x}, m_y {vector.m_y} {}
    Vector2l(const raylib::Vector2& vector) : m_x {vector.GetX()}, m_y {vector.GetY()} {}

    double GetX() {
	return m_x;
    }
    double GetY() {
	return m_y;
    }
    raylib::Vector2 GetVector2() {
	return raylib::Vector2 {static_cast<float>(m_x), static_cast<float>(m_y)};
    }
    void Add(const Vector2l& vector) {
	m_x += vector.m_x;
	m_y += vector.m_y;
    }
};

namespace structs {

struct Vector2l {
    double x, y;
};

class Vector2i {
public:
    int x;
    int y;
    
    bool operator==(const Vector2i& other) const {
        return x == other.x && y == other.y;
    }

};

}




namespace std {
    template<>
    struct hash<structs::Vector2i> {
        size_t operator()(const structs::Vector2i& v) const {
            size_t h1 = hash<int>{}(v.x);
            size_t h2 = hash<int>{}(v.y);
            return h1 ^ (h2 << 1); // or use boost::hash_combine style
        }
    };
}






class ChunkCoord {
private:
    structs::Vector2l local;      // Always in [0, 511)
    structs::Vector2i chunk;    // Tracks chunk position

    void normalize() {
        // Handle X
        while (local.x >= CHUNK_SIZE) {
            local.x -= CHUNK_SIZE;
            chunk.x++;
        }
        while (local.x < 0) {
            local.x += CHUNK_SIZE;
            chunk.x--;
        }

        // Handle Y
        while (local.y >= CHUNK_SIZE) {
            local.y -= CHUNK_SIZE;
            chunk.y++;
        }
        while (local.y < 0) {
            local.y += CHUNK_SIZE;
            chunk.y--;
        }
    }

public:
    ChunkCoord() : local{0, 0}, chunk{0, 0} {}

    ChunkCoord(structs::Vector2l localPos, structs::Vector2i chunkPos)
        : local(localPos), chunk(chunkPos) {
        normalize();  // Ensure consistency
    }

    // Setters
    void setLocal(structs::Vector2l pos) {
        local = pos;
        normalize();
    }

    void setLocalX(double x) {
        local.x = x;
        normalize();
    }

    void setLocalY(double y) {
        local.y = y;
        normalize();
    }

    void setChunk(structs::Vector2i c) {
        chunk = c;
    }

    void setChunkX(int x) {
        chunk.x = x;
    }

    void setChunkY(int y) {
        chunk.y = y;
    }

    // Getters
    structs::Vector2l getLocal() const { return local; }
    double getLocalX() const { return local.x; }
    double getLocalY() const { return local.y; }

    structs::Vector2i getChunk() const { return chunk; }
    int getChunkX() const { return chunk.x; }
    int getChunkY() const { return chunk.y; }
};







class Radian {
private:
    double radians;

    static double normalizeRadians(double rad) {
        rad = std::fmod(rad, TWO_PI);
        return rad < 0 ? rad + TWO_PI : rad;
    }

public:
    // Constructors
    Radian() : radians(0.0) {}
    explicit Radian(double rad) : radians(normalizeRadians(rad)) {}
    explicit Radian(const Degree& deg);  // Defined later

    // Getter and Setter for Radians
    double getRadians() const { return radians; }
    void setRadians(double rad) { radians = normalizeRadians(rad); }

    // Getter and Setter for Degrees
    Degree getDegrees() const;
    void setDegrees(Degree deg);
};

class Degree {
private:
    double degrees;

    static double normalizeDegrees(double deg) {
        deg = std::fmod(deg, 360.0);
        return deg < 0 ? deg + 360.0 : deg;
    }

public:
    // Constructors
    Degree() : degrees(0.0) {}
    explicit Degree(double deg) : degrees(normalizeDegrees(deg)) {}

    // Getter and Setter for Degrees
    double getDegrees() const { return degrees; }
    void setDegrees(double deg) { degrees = normalizeDegrees(deg); }

    // Getter and Setter for Radians
    double getRadians() const { return degrees * M_PI / 180.0; }
    void setRadians(double rad) { degrees = normalizeDegrees(rad * 180.0 / M_PI); }
};

// Implement cross-class methods
Radian::Radian(const Degree& deg) : radians(normalizeRadians(deg.getRadians())) {}

Degree Radian::getDegrees() const {
    return Degree(radians * 180.0 / M_PI);
}

void Radian::setDegrees(Degree deg) {
    radians = normalizeRadians(deg.getDegrees() * M_PI / 180.0);
}

class Player 
{
private:
    double m_speed;
    double m_maxSpeed;
    double m_acceleration;
    Radian m_direction;
    Degree m_degree;
    raylib::Rectangle m_rectangle;
public:
    Player(double speed, double maxSpeed, double acceleration, Degree direction) : m_speed {speed},
					     m_maxSpeed {maxSpeed},
					     m_direction {direction},
					     m_degree {direction.getDegrees()},
					     m_acceleration {acceleration},
					     m_rectangle {raylib::Vector2 {0, 0}, 
							  raylib::Vector2 {50, 25}}
    {}
    Degree getDirection()
    {
    return m_degree;
    }
    raylib::Rectangle getRectangle() {
	return m_rectangle;
    }
    void setDirection(Degree direction) {
	m_direction.setDegrees(direction);
	m_degree.setRadians(m_direction.getRadians());
    }
    void increaseSpeed() {
	if (m_speed <= m_maxSpeed)
	    m_speed += m_acceleration;
	else m_speed = m_maxSpeed;
    }
    void decreaseSpeed() {
	if (m_speed >= -(m_maxSpeed))
	    m_speed -= m_acceleration;
	else m_speed = -(m_maxSpeed);

    }
    raylib::Vector2 getVector() {
	return Vector2{static_cast<float>(m_speed * cos(m_direction.getRadians())),
		       static_cast<float>(m_speed * sin(m_direction.getRadians()))};
    }
    void rotate(Degree degree) {
	setDirection(Degree {m_direction.getDegrees().getDegrees() + degree.getDegrees()});
    }
    void move(Vector2l& world) {
	world.Add(getVector());
    }
    void draw() {
	m_rectangle.Draw(m_rectangle.GetSize() * 1/2.0, m_direction.getDegrees().getDegrees(), RED);
    }

};



void UpdateDrawFrame(Player player,
		     Vector2l worldLoc,
		     raylib::Camera2D camera
		     ) {



        //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);
    camera.BeginMode();

	
	player.draw();

    camera.EndMode();
    EndDrawing();
    //----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
// Main Entry Point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    Player player {0, 200 / FPS, 5 / FPS, Degree {0.0}};

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(FPS);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    raylib::Camera2D camera {raylib::Vector2 {0, 0}, raylib::Vector2 {0, 0}, 0.0f, 1.0f};
    Vector2l worldLoc {0, 0};

    std::unordered_map<structs::Vector2i, Chunk> chunkMap;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

	if (raylib::Keyboard::IsKeyDown(KEY_W))
	    player.increaseSpeed();
	if (raylib::Keyboard::IsKeyDown(KEY_S))
	    player.decreaseSpeed();
	if (raylib::Keyboard::IsKeyDown(KEY_A))
	    player.rotate(Degree {-1.0});
	if (raylib::Keyboard::IsKeyDown(KEY_D))
	    player.rotate(Degree {1.0});
	player.move(worldLoc);
	camera.SetOffset(raylib::Vector2 { screenWidth/2.0f, screenHeight/2.0f });
	camera.SetZoom(1.0f);
	camera.SetRotation((-player.getDirection().getDegrees()) + 90.0f);
	camera.SetTarget(raylib::Vector2 {player.getRectangle().GetPosition()});

	UpdateDrawFrame(player, worldLoc, camera);
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------

