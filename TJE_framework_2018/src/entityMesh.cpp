#include "entityMesh.h"
#include "utils.h"
#include "includes.h"
#include <iostream>


EntityMesh::EntityMesh() :Entity() {
	mesh = new Mesh();
	texture = new Texture();
	shader = new Shader();
}
EntityMesh::~EntityMesh() {
}

void EntityMesh::setup(const char* meshName, const char* textureName, const char* vsf, const char* psf) {
	
	mesh->Load(meshName);
	
	texture->Load(textureName);
	shader->Load(vsf, psf);

}
void EntityMesh::render(Camera *camera) {
	
	Matrix44 m = this->getGlobalMatrix();
	Matrix44 mvp = m * camera->viewprojection_matrix;

	glDisable(GL_DEPTH_TEST);

	glDepthMask(GL_FALSE);

	glDisable(GL_CULL_FACE);

	//enable shader
	shader->enable();

	//upload uniforms
	shader->setUniform("u_color", Vector4(1, 1, 1, 1));
	shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
	shader->setUniform("u_texture", texture);
	shader->setUniform("u_model", m);
	shader->setUniform("u_time", 0.0f);

	//current_shader->setUniform("u_model", m);
	mesh->render(GL_TRIANGLES, shader);




	for (int i = 0; i < this->children.size(); i++)
	{
		this->children[i]->render(camera);
	}

	glEnable(GL_CULL_FACE);


	glEnable(GL_DEPTH_TEST);

	glDepthMask(GL_TRUE);
}

Matrix44 EntityMesh::getGlobalMatrix() {
	if (parent)
		return model * parent->getGlobalMatrix();
	return model;
}