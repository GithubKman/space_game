
#include <iostream>
#include <string>

#include "raylib-cpp.hpp" // IWYU pragma: export
#include "raylib.h"
#include "rlgl.h"

#include "globals.hpp"
#include "chunk/chunk_coordinate.hpp"
#include "player/player.hpp"
#include "world/world.hpp"
#include <GLFW/glfw3.h>
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif
// Initialize tracking variables
float frameTime = 0.0f;
int frameCount = 0;
float fps = 0.0f;

void DrawDebugOverlay(int entityCount, int textureCount) {
    // Update metrics
    frameTime = GetFrameTime();
    frameCount++;
    fps = GetFPS();

    // Draw background box
    DrawRectangle(10, 10, 220, 100, Fade(DARKGRAY, 0.6f));

    // Print stats
    DrawText(TextFormat("FPS: %.1f", fps), 20, 20, 20, GREEN);
    DrawText(TextFormat("Frame Time: %.2f ms", frameTime * 1000), 20, 40, 20, LIGHTGRAY);
    DrawText(TextFormat("Entities: %d", entityCount), 20, 60, 20, ORANGE);
    DrawText(TextFormat("Textures: %d", textureCount), 20, 80, 20, SKYBLUE);
}
void UpdateDrawFrame(sms::Player& player,
		     sms::ChunkCoordinate& worldLoc,
		     raylib::Camera2D& camera,
		     raylib::Window& window,
		     sms::World& world) {



        //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    window.BeginDrawing();
    ClearBackground(GRAY);
    camera.BeginMode();
	world.draw(worldLoc);
	player.draw();
    camera.EndMode();
    DrawDebugOverlay(world.getEntityCount(), world.getTextureCount());
    window.EndDrawing();
    //----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
// Main Entry Point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    raylib::Window window {screenWidth, screenHeight, "raylib [core] example - basic window", FLAG_WINDOW_RESIZABLE | 
											      FLAG_WINDOW_HIGHDPI |
											      FLAG_WINDOW_ALWAYS_RUN | 
											      FLAG_MSAA_4X_HINT};
    sms::Player player {0, 2000, 100, 0.0};

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    //--------------------------------------------------------------------------------------

    raylib::Camera2D camera {{0, 0}, {0, 0}, 0.0f, 1.0f};
    sms::ChunkCoordinate worldLoc {{0, 0}, {0, 0}};
    float zoomSpeed {0.1f};
    float zoom {1};

    sms::World world {};
    std::cout << "["
	      << window.GetScaleDPI().GetX()
	      << ", "
	      << window.GetScaleDPI().GetY()
	      << "]\n";
    GLFWwindow* glfwWindow = (GLFWwindow*)GetWindowHandle();
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(glfwWindow, &fbWidth, &fbHeight);
    std::cout << fbWidth << " " << fbHeight << "\n";
    bool slowFPS {false};
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

	int fbWidthOld = fbWidth;
	int fbHeightOld = fbHeight;
	glfwGetFramebufferSize(glfwWindow, &fbWidth, &fbHeight);
	if (fbWidthOld != fbWidth || fbHeightOld != fbHeight) {
	    rlViewport(0, 0, fbWidth, fbHeight);
	    std::cout << window.GetRenderWidth() << " " << window.GetRenderHeight() << "\n";
	}
	
	float oldZoom = zoom;
	zoom += (GetMouseWheelMove() * zoomSpeed);
	if (zoom > 10) {
	    zoom = 10;
	}
	if (zoom < 0.1) {
	    zoom = 0.1;
	}

	if (zoom != oldZoom) {
	    std::cout << zoom << "\n";
	}

	if (raylib::Keyboard::IsKeyDown(KEY_W))
	    player.increaseSpeed();
	if (raylib::Keyboard::IsKeyDown(KEY_S))
	    player.decreaseSpeed();
	if (raylib::Keyboard::IsKeyDown(KEY_A))
	    player.rotate(-50.0 * GetFrameTime());
	if (raylib::Keyboard::IsKeyDown(KEY_D))
	    player.rotate(50.0 * GetFrameTime());
	if (raylib::Keyboard::IsKeyPressed(KEY_T)) {
	    sms::Vector2i loc {worldLoc.getChunk()};
	    worldLoc.setChunk(loc + loc);
	}
	if (raylib::Keyboard::IsKeyPressed(KEY_F)) {
	    slowFPS = !slowFPS;
	    std::cout << slowFPS << "\n";
	    if (slowFPS) {
		window.SetTargetFPS(-1);
		std::cout << "Uncapped\n";
	    }
	    else
		window.SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
	}
	worldLoc.addLocal(player.getVector());
	//worldLoc.print();
	
	camera.SetZoom(zoom);
	camera.SetTarget(player.getRectangle().GetPosition());
	camera.SetOffset(/*(player.getRectangle().GetSize() * 1/2) + */raylib::Vector2{static_cast<float>(window.GetRenderWidth()) / 2, static_cast<float>(window.GetRenderHeight()) / 2});
	camera.SetRotation((-static_cast<float>(player.getDirection().getDegrees() - 90.0f)));

	
	world.update(worldLoc);
	UpdateDrawFrame(player, worldLoc, camera, window, world);
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

