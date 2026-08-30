//
// Created by siii on 30-08-2026.
//
#include <filesystem>
#include <raylib.h>
#include "sceneBuilder.hpp"

namespace fs = std::filesystem;

SceneBuilder::SceneBuilder(uint64_t width, uint64_t height, uint64_t depth)
{
	for (auto entry : fs::recursive_directory_iterator("assets/sprites/terrain/"))
	{
		auto path = entry.path();

		//TODO: make case insensitive
		//Note: Cmake doesn't clean the assets directory, maybe a TODO?
		if (is_regular_file(path) && path.extension() == ".png")
		{
			m_terrainTextures.push_back(LoadTexture(path.c_str()));
			TraceLog(LOG_INFO, "Loaded: %s", path.filename().c_str());
		}
	}

	m_terrainPoints = new Texture2D[width * height * depth];
	m_width = width;
	m_height = height;
	m_depth = depth;
}

SceneBuilder::~SceneBuilder()
{

}

void SceneBuilder::Render()
{

}