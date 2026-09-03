//
// Created by siii on 30-08-2026.
//
#include <filesystem>
#include <raylib.h>
#include "sceneBuilder.hpp"

namespace fs = std::filesystem;

SceneBuilder::SceneBuilder(uint32_t width, uint32_t height, uint32_t depth)
{
	for (const auto& entry : fs::recursive_directory_iterator("assets/sprites/terrain/"))
	{
		const auto& path = entry.path();
		if (is_regular_file(path) && path.extension() == ".png")
		{
			m_terrainTextures[path.stem()] = LoadTexture(path.c_str());
		}
	}

	m_terrainPoints = new size_t[width * height * depth];

	m_width = width;
	m_height = height;
	m_depth = depth;

	Mesh worldFloor = GenMeshCube(width, 1.0f, depth);

	if (!m_terrainTextures.contains("Ordanium"))
	{
		TraceLog(LOG_FATAL, "WORLD HAS NO FLOOR, CANNOT CONTINUE (please ensure the Ordanium texture exists!)");
		exit(EXIT_FAILURE);
	}

	Texture2D& ordanium = m_terrainTextures["Ordanium"];


	 for (size_t i = 0; i < worldFloor.vertexCount; i++)
	 {
	 	if (worldFloor.normals[i * 3 + 1] > 0.5f)//if up or down
	 	{
	 		worldFloor.texcoords[i * 2] *= width;
	 		worldFloor.texcoords[i * 2 + 1] *= depth;
	 	}
	 	else
	 	{
	 		worldFloor.texcoords[i * 2] *= width; //it doesn't need extra repetition on height because its 1 tall
	 	}
	 }

	SetTextureWrap(ordanium, TEXTURE_WRAP_REPEAT);
	UpdateMeshBuffer(worldFloor, 1, worldFloor.texcoords, sizeof(float) * worldFloor.vertexCount * 2, 0);

	m_worldFloor = LoadModelFromMesh(worldFloor);

	m_worldFloor.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = ordanium;

	m_model = LoadModelFromMesh({});

}

SceneBuilder::~SceneBuilder()
{
	for (std::pair<const std::string, Texture>& stringTexture : m_terrainTextures)
	{
		UnloadTexture(stringTexture.second);
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