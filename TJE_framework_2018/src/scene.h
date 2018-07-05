#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "framework.h"

#include <string>
#include "camera.h"
#include "includes.h"
#include "camera.h"
#include "utils.h"
#include "entity.h"
#include "entityMesh.h"
class Scene
{
private:
	Scene();//constructor
	~Scene();//destructor
public:
	static Scene* instance;
	Entity* root;
	EntityMesh* sky;

	static Scene* getInstance() {
		if (instance == NULL) instance = new Scene();
		return instance;
	};
	std::vector<Entity*> children;
	void addChild(Entity *child );
	void removeChild(Entity *child);
	void setup();
	virtual void render(Camera * camera);
	virtual void update(float elapsed_time);

};
#endif