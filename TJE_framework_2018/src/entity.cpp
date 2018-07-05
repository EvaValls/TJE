#include "entity.h"
#include "utils.h"
#include "includes.h"
#include <iostream>

Entity::Entity() {
	parent = NULL;
}
Entity::~Entity() {
}
void Entity::setName(std::string n) {
	name = n;
}
void Entity::render(Camera *camera) {
	for (int i = 0; i < children.size(); i++) {
		children[i]->render(camera);
	}
}
void Entity::update(float et) {
	for (int i = 0; i < children.size(); i++) {
		children[i]->update(et);
	}
}
void Entity::addChild(Entity *child) {
	children.push_back(child);
	child->parent = this;
}

void Entity::removeChild(Entity *child) {
	to_destroy.push_back(child);
}
void Entity::removeAll() {
	for (int i = 0; i < to_destroy.size(); i++) {
		if(to_destroy[i]->children.size()>0) {
			to_destroy[i]->children.clear();
		}
		delete to_destroy[i];
	}
	to_destroy.clear();
}

Matrix44 Entity::getGlobalMatrix() {
	if (parent)
		return model * parent->getGlobalMatrix();
	return model;
}

Vector3 Entity::getPosition() {
	return model * Vector3();
}