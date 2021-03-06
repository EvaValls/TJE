#ifndef ENTITYMESH_H
#define ENTITYMESH_H

#include <vector>
#include "framework.h"
#include "entity.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include <map>
#include <string>

class EntityMesh : public Entity {
public:
	EntityMesh(bool isStatic, bool hasBlending);//constructor
	~EntityMesh();//destructor

	Mesh* mesh;
	Texture* texture;
	Shader* shader;
	Vector4 color;
	bool is_static;
	void setup(const char* meshName, const char* textureName, const char* vsf, const char* psf);
	void render(Camera * camera);
	Matrix44 getGlobalMatrix();
	void update(float elapsed_time) {};

};
#endif	
