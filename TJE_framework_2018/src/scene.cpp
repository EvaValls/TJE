#include "scene.h"

#include "includes.h"
#include "utils.h"
#include <iostream>

Scene * Scene::instance = NULL;
Scene::Scene() {
	root = new Entity(false, false);
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
	
	sky = new EntityMesh(true, false);
	sky->setName("sky");
	Vector3 center = Camera::current->center;
	//sky->model.scale(3, 3, 3);
	sky->model.setTranslation(center.x, center.y, center.z);
	sky->model.setScale(0.5, 0.5, 0.5);
	sky->setup("data/sky/cielo.ASE", "data/sky/cielo.tga", "data/shaders/basic.vs", "data/shaders/texture.fs");


	Entity* ground = new Entity(false, false);
	EntityMesh* house1 = new EntityMesh(false, false);
	EntityMesh* bunker = new EntityMesh(false, false);
	EntityMesh* airport = new EntityMesh(false, false);
	

	airport->setName("airport");
	airport->model.scale(0.3,0.3,0.3);
	//airport->setup("data/terrain_airport/terrain_airport.ASE", "data/terrain_airport/terrain_airport.tga", "data/shaders/basic.vs", "data/shaders/texture.fs");
	airport->setup("data/island.ASE", "data/island.tga", "data/shaders/basic.vs", "data/shaders/texture.fs");

	house1->setup("data/terrain_props/house1.ASE", "data/terrain_props/houses_and_windows.tga", "data/shaders/basic.vs", "data/shaders/texture.fs");
	bunker->setup("data/terrain_props/bunker.ASE", "data/terrain_props/bunkers_and_forts.tga", "data/shaders/basic.vs", "data/shaders/texture.fs");
	bunker->model.setTranslation(-100, 2, 1);
	ground->addChild(airport);
	ground->addChild(house1);
	ground->addChild(bunker);

	EntityMesh* water = new EntityMesh(false, false);
	water->setName("water");
	water->setup("data/agua/agua.ASE", "data/agua/agua.tga", "data/shaders/basic.vs", "data/shaders/water.fs");
	water->model.setTranslation(center.x, center.y, center.z);
	root->addChild((Entity*)water);

	root->addChild(sky);
	root->addChild(ground);


}
void Scene::render(Camera * camera) {
	
	Vector3 center = camera->center;
	sky->model.setTranslation(center.x, center.y, center.z);
	sky->render(camera);

	root->render(camera);
}
void Scene::update(float elapsed_time) {
	
}