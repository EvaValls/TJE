#include "game.h"
#include "utils.h"
#include "mesh.h"
#include "texture.h"
#include "fbo.h"
#include "shader.h"
#include "input.h"

#include <cmath>

//some globals
/*Mesh* mesh = NULL;
Texture* texture = NULL;
Shader* shader = NULL;*/

float angle = 0;

Game* Game::instance = NULL;

Game::Game(int window_width, int window_height, SDL_Window* window)
{
	
	this->window_width = window_width;
	this->window_height = window_height;
	this->window = window;
	instance = this;
	must_exit = false;

	fps = 0;
	frame = 0;
	time = 0.0f;
	elapsed_time = 0.0f;
	mouse_locked = false;

	//OpenGL flags
	glEnable( GL_CULL_FACE ); //render both sides of every triangle
	glEnable( GL_DEPTH_TEST ); //check the occlusions using the Z buffer

	//create our camera
	camera = new Camera();
	camera->lookAt(Vector3(0.f,100.f, 100.f),Vector3(-10.f,-10.f,-10.f), Vector3(0.f,1.f,0.f)); //position the camera and point to 0,0,0
	camera->setPerspective(70.f,window_width/(float)window_height,0.1f,10000.f); //set the projection, we want to be perspective
	Camera::current = camera;

	scene = Scene::getInstance();
	scene->setup();
	//create a plane mesh
	/*mesh = Mesh::Load("data/box.ASE");

	//load one texture
	texture = new Texture();
 	texture->load("data/texture.tga");

	// example of shader loading
	shader = Shader::Load("data/shaders/basic.vs", "data/shaders/texture.fs");
	*/
	//hide the cursor
	SDL_ShowCursor(!mouse_locked); //hide or show the mouse
}

//what to do when the image has to be draw
void Game::render(void)
{
	//set the clear color (the background color)
	glClearColor(0.62, 0.75, 0.79, 1.0);
	//glClearColor(0.12, 0.20, 0.23, 1.0);
	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set the camera as default
	camera->enable();
	scene->render(camera);
	
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_BLEND);

   /*
	//create model matrix for cube
	Matrix44 m;
	m.rotate( (float)(angle * DEG2RAD), Vector3(0.0f,1.0f, 0.0f) ); //build a rotation matrix
	//scene->render(camera);
	Shader* current_shader = shader;

	if(current_shader)
	{
		//enable shader
		current_shader->enable();

		//upload uniforms
		current_shader->setUniform("u_color", Vector4(1,1,1,1));
		current_shader->setUniform("u_viewprojection", camera->viewprojection_matrix );
		current_shader->setUniform("u_texture", texture);
		current_shader->setUniform("u_model", m);
		current_shader->setUniform("u_time", time);

		//current_shader->setUniform("u_model", m);
		mesh->render(GL_TRIANGLES, current_shader);

		//disable shader
		current_shader->disable();
	}*/

	//Draw out world
	//drawGrid();

	//render the FPS
	//drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//swap between front buffer and back buffer
	SDL_GL_SwapWindow(this->window);
}

void Game::update(double seconds_elapsed)
{
	float speed = seconds_elapsed * 200; //the speed is defined by the seconds_elapsed so it goes constant

	//example
	angle += (float)seconds_elapsed * 10.0f;

	//mouse input to rotate the cam
	if ((Input::mouse_state & SDL_BUTTON_LEFT) || mouse_locked ) //is left button pressed?
	{
		camera->rotate(Input::mouse_delta.x * 0.005f, Vector3(0.0f,-1.0f,0.0f));
		camera->rotate(Input::mouse_delta.y * 0.005f, camera->getLocalVector( Vector3(-1.0f,0.0f,0.0f)));
	}

	//async input to move the camera around
	if(Input::isKeyPressed(SDL_SCANCODE_LSHIFT) ) speed *= 100; //move faster with left shift
	if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) camera->move(Vector3(0.0f, 0.0f, 1.0f) * speed);
	if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) camera->move(Vector3(0.0f, 0.0f,-1.0f) * speed);
	if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT)) camera->move(Vector3(1.0f, 0.0f, 0.0f) * speed);
	if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) camera->move(Vector3(-1.0f,0.0f, 0.0f) * speed);

	//to navigate with the mouse fixed in the middle
	if (mouse_locked)
		Input::centerMouse();
	scene->update(seconds_elapsed);
}

//Keyboard event handler (sync input)
void Game::onKeyDown( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: must_exit = true; break; //ESC key, kill the app
		case SDLK_F1: Shader::ReloadAll(); break; 
	}
}

void Game::onKeyUp(SDL_KeyboardEvent event)
{
}

void Game::onGamepadButtonDown(SDL_JoyButtonEvent event)
{

}

void Game::onGamepadButtonUp(SDL_JoyButtonEvent event)
{

}

void Game::onMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_MIDDLE) //middle mouse
	{
		mouse_locked = !mouse_locked;
		SDL_ShowCursor(!mouse_locked);
	}
}

void Game::onMouseButtonUp(SDL_MouseButtonEvent event)
{
}

void Game::onResize(int width, int height)
{
    std::cout << "window resized: " << width << "," << height << std::endl;
	glViewport( 0,0, width, height );
	camera->aspect =  width / (float)height;
	window_width = width;
	window_height = height;
}

