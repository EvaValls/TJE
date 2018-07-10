#include "entityMesh.h"
#include "utils.h"
#include "includes.h"
#include "game.h"
#include <iostream>


EntityMesh::EntityMesh(bool isStatic) :Entity(){
	mesh = new Mesh();
	texture = new Texture();
	shader = new Shader();
	is_static = isStatic;
}
EntityMesh::~EntityMesh() {
}

void EntityMesh::setup(const char* meshName, const char* textureName, const char* vsf, const char* psf) {

	mesh = Mesh::Load(meshName);
	texture = Texture::Load(textureName);
	shader = Shader::Load(vsf, psf);

}
void EntityMesh::render(Camera *camera) {
	//set the clear color (the background color)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Matrix44 m = this->getGlobalMatrix();
	Matrix44 mvp = m * camera->viewprojection_matrix;
	Vector3 center = mesh->box.center;
	Vector3 position = m * center;

	if (!camera->testSphereInFrustum(position, mesh->radius))
		return;
	if (is_static)
		glDisable(GL_DEPTH_TEST);
	//enable shader
	shader->enable();

	//upload uniforms
	
	shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
	shader->setTexture("u_texture", texture);
	shader->setUniform("u_color", Vector4(1, 1, 1, 1));
	shader->setUniform("u_model", m);
	shader->setVector3("u_camera_pos", camera->eye);
	shader->setUniform("u_time", 0.0f);

	mesh->render(GL_TRIANGLES, shader);
	shader->disable();
	if (is_static)
		glEnable(GL_DEPTH_TEST);
	
	for (int i = 0; i < this->children.size(); i++)
	{
		this->children[i]->render(camera);
	}
	//SDL_GL_SwapWindow(Game::instance->window);
}

Matrix44 EntityMesh::getGlobalMatrix() {
	if (parent)
		return model * parent->getGlobalMatrix();
	return model;
}