#include <fstream>
#include <raylib.h>
#include <string>

#include "json.hpp"
#include "scene.hpp"
#include "ScenarioBuilder/sceneBuilder.hpp"

using json = nlohmann::json;

int main()
{

	std::ifstream f("assets/settings.json");
	json config = json::parse(f, nullptr, false);

	config = config.is_discarded() ? json::object() : config;

	const int   width = json_getOrDefault<int>(config, "width", 800),
	            height = json_getOrDefault<int>(config, "height", 600),
	            targetFPS = json_getOrDefault<int>(config, "targetFPS", 60);

	InitWindow(width, height, "Caliburner");

	SetTargetFPS(targetFPS);

	Scene* scene = new SceneBuilder();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);


		EndDrawing();
	}

	return 0;
}