//
// Created by siii on 29-08-2026.
//

#ifndef CALIBURNER_LEVEL_HPP
#define CALIBURNER_LEVEL_HPP
#include <string>
#include "gridCoord.hpp"
#include "terrain.hpp"

enum class GameMode {Kerfuffle, EmbarkOnLegend};

NLOHMANN_JSON_SERIALIZE_ENUM(GameMode, {
    {GameMode::Kerfuffle, "Kerfuffle"},
    {GameMode::EmbarkOnLegend, "EmbarkOnLegend"},
})

class Level
{
public:
	Level(std::string const &levelName);
	~Level();
	void Render();
private:
//Meta data
	std::string m_name;
	std::string m_description;
	std::string m_version;
	std::string m_author;
	uint8_t m_maxPlayers;
	GameMode m_gameMode;
//Map data
	std::unordered_map<GridCoord, Terrain, GridCoordHash> m_terrain;
};


#endif //CALIBURNER_LEVEL_HPP
