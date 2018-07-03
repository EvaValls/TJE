#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "framework.h"

#include <map>
#include <string>
#include "entity.h"
class Scene
{
public:
	Scene();//constructor
	~Scene();//destructor
	static  Scene * getInstance() {
		if (instance == NULL) instance = new Scene();
		return instance;
	};
	std::vector<Entity*> children;
	void addChild(Entity *child);
	void removeChild(Entity *child);
	virtual void render();
	virtual void update(float elapsed_time);

}
