#include "scene.h"

#include "includes.h"
#include "utils.h"
#include <iostream>

Scene * Scene::instance = NULL;
Scene::Scene() {
	root = new Entity();
	sky = NULL;
	instance = this;

}
Scene::~Scene() {

}

void Scene::addChild(Entity *child) {
	children.push_back(child);
}

void Scene::removeChild(Entity *child) {

}
void Scene::setup() {

	// WORLD
	//sky->setName("sky");
	sky = new EntityMesh(true);
	sky->setup("data/sky/cielo.ASE", "data/sky/cielo.tga", "data/shaders/basic.vs", "data/shaders/texture.fs");
	
	/*EntityMesh* sea = new EntityMesh();
	sea->setName("sea");
	sea->setup("agua.ASE", "data/textures/agua.tga", "data/shaders/basic.vs", "data/shaders/texture.fs");
	//sea->model.setTranslation(i * 10001, -10, j * 10001);
	root->addChild((Entity*)sea);*/
	//root->addChild(sky);

	Entity* ground = new Entity();
	EntityMesh* house1 = new EntityMesh(true);
	EntityMesh* bunker = new EntityMesh(true);
	EntityMesh* airport = new EntityMesh(true);
	airport->setName("airport");
	airport->setup("data/terrain_airport/terrain_airport.ASE", "data/terrain_airport/terrain_airport.tga", "data/shaders/basic.vs", "data/shaders/texture.fs");
	house1->setup("data/terrain_props/house1.ASE", "data/terrain_props/houses_and_windows.tga", "data/shaders/basic.vs", "data/shaders/texture.fs");
	house1->model.setIdentity();
	bunker->setup("data/terrain_props/bunker.ASE", "data/terrain_props/bunkers_and_forts.tga", "data/shaders/basic.vs", "data/shaders/texture.fs");
	bunker->model.setTranslation(-100, 2, 1);
	ground->addChild(airport);
	ground->addChild(house1);
	ground->addChild(bunker);
	root->addChild(ground);
	root->addChild(sky);
	
}
void Scene::render(Camera * camera) {
	root->render(camera);
	//sky->render(camera);
	
}
void Scene::update(float elapsed_time) {}