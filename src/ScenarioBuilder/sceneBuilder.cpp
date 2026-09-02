//
// Created by siii on 30-08-2026.
//
#include <filesystem>
#include <raylib.h>
#include "sceneBuilder.hpp"

namespace fs = std::filesystem;

SceneBuilder::SceneBuilder(uint64_t width, uint64_t height, uint64_t depth)
{
	size_t counter = 0;

	for (const auto& entry : fs::recursive_directory_iterator("assets/sprites/terrain/"))
	{
		const auto& path = entry.path();
		if (is_regular_file(path) && path.extension() == ".png")
		{
			counter++;
		}
	}
	m_terrainTextures = new Texture2D[counter];
	m_terrainTextures_count = counter;

	counter = 0;
	for (const auto& entry : fs::recursive_directory_iterator("assets/sprites/terrain/"))
	{
		const auto& path = entry.path();
		if (is_regular_file(path) && path.extension() == ".png")
		{
			m_terrainTextures[counter++] = LoadTexture(path.c_str());
		}
	}

	m_terrainPoints = new size_t[width * height * depth];

	m_width = width;
	m_height = height;
	m_depth = depth;

	Mesh worldFloor = GenMeshCube(width, 1.0f, depth);


	for (int i = 0; i < worldFloor.vertexCount; i++)
	{
		worldFloor.texcoords[i * 2 + 0] *= width;
		worldFloor.texcoords[i * 2 + 1] *= depth;
	}

	SetTextureWrap(m_terrainTextures[0], TEXTURE_WRAP_REPEAT);

	m_worldFloor = LoadModelFromMesh(worldFloor);
	m_worldFloor.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_terrainTextures[0];

	m_model = LoadModelFromMesh({});

}

SceneBuilder::~SceneBuilder()
{
	for (size_t i = 0; i < m_terrainTextures_count; i++)
	{
		UnloadTexture(m_terrainTextures[i]);
	}
	UnloadModel(m_model);
	delete m_terrainPoints;
}

void SceneBuilder::Render()
{
	DrawModel(m_worldFloor, {.x = 0,.y = 0,.z = 0}, 1, WHITE);
}

void SceneBuilder::RenderUI()
{
}