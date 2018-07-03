#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "framework.h"

#include <map>
#include <string>
class Entity
{
public:
	Entity();//constructor
	virtual ~Entity();//destructor

	std::string name;
	Entity *parent;
	Matrix44 model;
	std::vector<Entity*> children;

	virtual void render();
	virtual void update(float elapsed_time);

	void addChild(Entity *child);
	void removeChild(Entity *child);
	void move(Vector3 mov);
	void rotate(Vector3 mov, float angle);
	Vector3 getPosition();
	Matrix44 getGlobalMatrix();
}
