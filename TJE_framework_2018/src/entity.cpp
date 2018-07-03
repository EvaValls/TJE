#include "entity.h"
#include "utils.h"
#include "includes.h"
#include <iostream>

Entity * Entity::instance = NULL;
Entity::Entity() {
	parent = null;
}
Entity::~Entity() {
}

void Entity::render() {
	for (int i = 0; i < children.size(); i++) {
		children[i]->render();
	}
}

Matrix44 Entity::getGlobalMatrix() {
	if (parent)
		return model * parent->getGlobalMatrix();
	return model;
}