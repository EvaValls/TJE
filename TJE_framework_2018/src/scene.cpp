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
	sky = new EntityMesh();
	sky->setup("data/sky/cubemap.ASE", "data/sky/cielo.tga", "data/shaders/basic.vs", "data/shaders/texture.fs");
	
	/*EntityMesh* sea = new EntityMesh();
	sea->setName("sea");
	sea->setup("agua.ASE", "data/textures/agua.tga", "data/shaders/basic.vs", "data/shaders/texture.fs");
	//sea->model.setTranslation(i * 10001, -10, j * 10001);
	root->addChild((Entity*)sea);*/


	Entity* ground = new Entity();
	EntityMesh* house1 = new EntityMesh();

	house1->setup("data/terrain_props/house1.ASE", "data/terrain_props/houses_and_windows.tga", "data/shaders/basic.vs", "data/shaders/texture.fs");
	house1->model.setIdentity();
	ground->addChild((Entity*)house1);
	root->addChild(ground);

	//map_entities.push_back(ground);
}
void Scene::render(Camera * camera) {
	sky->render(camera);
	
	root->render(camera);
	
}
void Scene::update(float elapsed_time) {}