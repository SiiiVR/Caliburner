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
	SceneBuilder(uint64_t width, uint64_t height, uint64_t depth);
	~SceneBuilder();

	void Render() override;
private:
	list<Texture2D> m_terrainTextures;
	Texture2D* m_terrainPoints;
	uint64_t m_width;
	uint64_t m_height;
	uint64_t m_depth;
};


#endif //CALIBURNER_SCENEBUILDER_HPP
