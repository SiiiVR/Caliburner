#include <fstream>
#include <nlohmann/json.hpp>
#include <raylib.h>
#include <string>

#include "level.hpp"

using json = nlohmann::json;


int main()
{

	std::ifstream f("assets/settings.json");
	json config = json::parse(f, nullptr, false);

	config = config.is_discarded() ? json::object() : config;

	const int   width = config.value<int>("width", 800),
	            height = config.value<int>("height", 600),
	            targetFPS = config.value<int>("targetFPS", 60);

	InitWindow(width, height, "Caliburner");

	Level* currentLevel = new Level(config["initialLevel"].get<std::string>());

	SetTargetFPS(targetFPS);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		currentLevel->Render();

		EndDrawing();
	}

	if (currentLevel) delete currentLevel;

	return 0;
}