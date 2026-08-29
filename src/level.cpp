//
// Created by siii on 29-08-2026.
//
#include <fstream>
#include <format>
#include <nlohmann/json.hpp>
#include "level.hpp"
#include <iostream>
#include <unordered_map>

using json = nlohmann::json;

Level::Level(std::string const& levelName)
{
    const std::string location = std::format("assets/levels/{}.json", levelName);
    std::ifstream f(location);
    json config = json::parse(f);

    //Do type checking
    m_name = levelName;
    m_version = config["version"].get<std::string>();
    m_description = config["description"].get<std::string>();
    m_author = config["author"].get<std::string>();
    m_maxPlayers = config["maxPlayers"].get<uint8_t>();
    m_gameMode = config["gameMode"].get<GameMode>();

    auto terrainPieces = config["terrain"];

    //TODO: Optimize this
    for (auto piece : terrainPieces)
    {
        GridCoord coord{
            .x = piece["x"],
            .y = piece["y"],
            .z = piece["z"]
        };

        Terrain terrain{
            piece["type"]
        };

        m_terrain[coord] = terrain;
    }

    std::cout << "Loaded: " << m_name << ", " << m_version
    << "\nAuthor:" << m_author
    << "\nmaxPlayers:" << m_maxPlayers << std::endl;
}

Level::~Level() = default;

void Level::Render()
{
    //TODO: Render level (requires loading assets)
}
