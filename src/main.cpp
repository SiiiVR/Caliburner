#include <fstream>
#include <raylib.h>
#include "json.hpp"
#include "scene.hpp"
#include "ScenarioBuilder/sceneBuilder.hpp"

using json = nlohmann::json;

int main()
{
	std::ifstream f("assets/settings.json");
	json config = json::parse(f, nullptr, false);

	config = config.is_discarded() ? json::object() : config;

	const int  width = json_getOrDefault<int>(config, "width", 800),
	           height = json_getOrDefault<int>(config, "height", 600),
	           targetFPS = json_getOrDefault<int>(config, "targetFPS", 60);

	const bool showFPS = json_getOrDefault<bool>(config, "showFPS", false);

	InitWindow(width, height, "Caliburner");

	SetTargetFPS(targetFPS);

	float distance = 25.f;
	Camera3D camera{
		 {distance, distance * sqrtf(2.0f / 3.0f), distance},
		{0,0,0},
		{0,1,0},
		distance,
		CAMERA_ORTHOGRAPHIC
	};

	Scene* scene = new SceneBuilder(10, 10, 10);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		BeginMode3D(camera);

		DrawGrid(10, 1.0f);
		scene->Render();

		scene->RenderUI();

		EndMode3D();

		if (showFPS) DrawFPS(0,0);

		EndDrawing();
	}

	delete scene;

	return 0;
}