//
// Created by siii on 30-08-2026.
//

#ifndef CALIBURNER_SCENEBUILDER_HPP
#define CALIBURNER_SCENEBUILDER_HPP
#include "scene.hpp"
#include <raylib.h>
#include <list>

using std::list;

class SceneBuilder : public Scene
{
public:
	SceneBuilder(uint32_t width, uint32_t height, uint32_t depth);
	~SceneBuilder();

	void Render() override;
	void RenderUI() override;
private:
	Model m_model{};
	Model m_worldFloor{};
	Texture2D* m_terrainTextures;
	size_t m_terrainTextures_count;
	size_t* m_terrainPoints;

	uint64_t m_width;
	uint64_t m_height;
	uint64_t m_depth;
};


#endif //CALIBURNER_SCENEBUILDER_HPP
