//
// Created by siii on 30-08-2026.
//
#include <filesystem>
#include <raylib.h>
#include "sceneBuilder.hpp"

namespace fs = std::filesystem;

SceneBuilder::SceneBuilder(uint64_t width, uint64_t height, uint64_t depth)
{
	for (const auto& entry : fs::recursive_directory_iterator("assets/sprites/terrain/"))
	{
		const auto& path = entry.path();

		//TODO: make case insensitive
		//Note: Cmake doesn't clean the assets directory, maybe a TODO?
		if (is_regular_file(path) && path.extension() == ".png")
		{
			m_terrainTextures.push_back(LoadTexture(path.c_str()));
			TraceLog(LOG_INFO, "Loaded: %s", path.filename().c_str());
		}
	}

	m_terrainPoints = new Texture2D*[width * height * depth];
	m_width = width;
	m_height = height;
	m_depth = depth;

	Mesh terrainMesh;

	for (uint64_t x = 0; x < width; x++)
	{
		for (uint64_t y = 0; y < height; y++)
		{
			for (uint64_t z = 0; z < depth; z++)
			{
				uint64_t x1 = x, y1 = y, z1 = z, x2 = x+1, y2= y+1, z2= z+1;
				bool topFrontLeft = m_terrainPoints[x1 + y1 * (width) + z1 * (width * height)];
				bool topFrontRight = m_terrainPoints[x2 + y1 * (width) + z1 * (width * height)];
				bool topBackLeft = m_terrainPoints[x1 + y2 * (width) + z1 * (width * height)];
				bool topBackRight = m_terrainPoints[x1 + y1 * (width) + z2 * (width * height)];
				bool bottomFrontLeft = m_terrainPoints[x2 + y2 * (width) + z2 * (width * height)];
				bool bottomFronRight = m_terrainPoints[x1 + y2 * (width) + z2 * (width * height)];
				bool bottomBackLeft = m_terrainPoints[x2 + y1 * (width) + z2 * (width * height)];
				bool bottomBackRight = m_terrainPoints[x2 + y2 * (width) + z1 * (width * height)];

				//only use the vertices that are one true.
				//And then build the faces from that
			}
		}
	}
}

SceneBuilder::~SceneBuilder()
{
	for (const auto texture : m_terrainTextures)
	{
		UnloadTexture(texture);
	}
	delete m_terrainPoints;
}

void SceneBuilder::Render()
{
}

void SceneBuilder::RenderUI()
{
}