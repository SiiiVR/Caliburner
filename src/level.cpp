//
// Created by siii on 29-08-2026.
//
#include <fstream>
#include <format>
#include "json.hpp"
#include "level.hpp"
#include <iostream>
#include <unordered_map>

Level::Level(std::string const& levelName)
{
	std::string path = std::format("assets/levels/{}.json", levelName);
	std::ifstream f(path);
	json config = json::parse(f, nullptr, false);

	config = config.is_discarded() ? json::object() : config;


	m_name = levelName;
	m_version = json_getOrDefault<std::string>(config, "version", "Unknown");
	m_description = json_getOrDefault<std::string>(config, "description", "");
	m_author = json_getOrDefault<std::string>(config, "author", "A conspicuous fellow.");
	m_maxPlayers = json_getOrDefault<uint8_t>(config, "maxPlayers", 0);
	m_gameMode = json_getOrDefault<GameMode>(config, "gameMode", GameMode::Kerfuffle);

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
