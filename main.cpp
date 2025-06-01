
#include "raylib-cpp.hpp" // IWYU pragma: export

#include "globals.h"
#include "chunk-coordinate.hpp"
#include "chunk_map.hpp"
#include "player.hpp"
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame(sms::Player player,
		     sms::ChunkCoordinate worldLoc,
		     raylib::Camera2D camera,
		     sms::ChunkMap& chunkMap) {



        //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(BLACK);
    camera.BeginMode();

	
	
	chunkMap.draw(worldLoc);
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
    raylib::Window window {screenWidth, screenHeight, "raylib [core] example - basic window", FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI};
    sms::Player player {0, 200 / framesPerSecond, 5 / framesPerSecond, 0.0};

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    window.SetTargetFPS(framesPerSecond);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    raylib::Camera2D camera {{0, 0}, {0, 0}, 0.0f, 1.0f};
    sms::ChunkCoordinate worldLoc {{0, 0}, {0, 0}};

    sms::ChunkMap chunkMap {};
    std::cout << "["
	      << window.GetScaleDPI().GetX()
	      << ", "
	      << window.GetScaleDPI().GetY()
	      << "]\n";
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

	if (raylib::Keyboard::IsKeyDown(KEY_W))
	    player.increaseSpeed();
	if (raylib::Keyboard::IsKeyDown(KEY_S))
	    player.decreaseSpeed();
	if (raylib::Keyboard::IsKeyDown(KEY_A))
	    player.rotate(-1.0);
	if (raylib::Keyboard::IsKeyDown(KEY_D))
	    player.rotate(1.0);
	worldLoc.addLocal(player.getVector());
	//worldLoc.print();
	camera.SetZoom(1.25);
	camera.SetTarget(player.getRectangle().GetPosition());
	camera.SetOffset(/*(player.getRectangle().GetSize() * 1/2) + */raylib::Vector2{static_cast<float>(window.GetWidth()) / 2, static_cast<float>(window.GetHeight()) / 2});
	camera.SetRotation((-player.getDirection().getDegrees()) + 90.0);

	UpdateDrawFrame(player, worldLoc, camera, chunkMap);
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

