//
// Created by siii on 30-08-2026.
//

#ifndef CALIBURNER_SCENE_HPP
#define CALIBURNER_SCENE_HPP


class Scene
{
public:
	virtual ~Scene() = 0;
	virtual void Render() = 0;
	virtual void RenderUI() = 0;
};


#endif //CALIBURNER_SCENE_HPP
