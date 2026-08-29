#include <fstream>
#include <nlohmann/json.hpp>
#include <raylib.h>
#include <string>

#include "level.hpp"

using json = nlohmann::json;

int main()
{
    std::ifstream f("assets/settings.json");
    json config = json::parse(f);

    int width = config["width"].get<int>();
    int height = config["height"].get<int>();
    int targetFPS = config["targetFPS"].get<int>();

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