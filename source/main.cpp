#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "gl.h"
#include "window.h"
#include "settings.h"
#include "dbg.h"

#include "shader.h"
#include "camera.h"
#include "_math.h"
#include "lighting.h"
#include "cubes.h"
#include "text.h"
#include "player.h"
#include "obj.h"
#include "input.h"
#include "level.h"
#include "audio.h"

Settings settings(800, 600);

slice_s test_slice = 
{
	{ 
	  {1, 1, 1, 1, 1, 1, 1, 1, 1},  
	  {1, 0, 0, 0, 0, 0, 0, 0, 1}, 
	  {1, 0, 0, 0, 0, 0, 0, 0, 1}, 
	  {1, 0, 0, 0, 0, 0, 0, 0, 1}, 
	  {1, 1, 0, 0, 1, 0, 0, 0, 1}, 
	  {1, 0, 0, 0, 0, 0, 0, 0, 1}, 
	  {1, 0, 0, 0, 0, 0, 0, 0, 1}, 
	  {1, 0, 0, 0, 0, 0, 0, 0, 1}, 
	  {1, 1, 1, 1, 1, 1, 1, 1, 1}
	}	
};

int main(void)
{
	windowInit();
	glewInit();
	audioInit();
	textInit();

	Camera camera(0.001f, 100.0f);

	camera.setPosition(glm::vec3(-5.0f, 10.0f, -10.0f));
	camera.view3 = glm::mat3(glm::rotate(glm::mat4(1.0f), float(M_PI / 4), glm::vec3(1.0f, 0.0f, 0.0f))) * glm::mat3(glm::rotate(glm::mat4(1.0f), float(3 * M_PI / 4), glm::vec3(0.0f, 1.0f, 0.0f)));

	Lighting lighting;

	lighting.setLightPosition(0, glm::vec3(2.0f, 2.0f, 2.0f));
	lighting.setLightEnabled(0, true);
	lighting.setLightShininess(0, 3.0f);

	glViewport(0, 0, settings.width, settings.height);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	float angle = 0.0f;
	float angle2 = 0.0f;

	Player player;
	Text text("hello", glm::vec2(0.0, 0.0));

	Level level;

	level.addSliceLayer(0, test_slice);
	level.addSliceLayer(0, test_slice);
	level.addSliceLayer(0, test_slice);

	level.addSliceLayer(1, test_slice);

	double lastFrame = glfwGetTime();

	// Sound sound("drumloop.wav");

	// sound.play();

	while(windowUpdate())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		double currentFrame = glfwGetTime();
		double deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if(Input::isKeyHold(GLFW_KEY_W)) camera.movePositionDouble(glm::dvec3(0.0, 0.0, -2.0) * deltaTime);
		if(Input::isKeyHold(GLFW_KEY_S)) camera.movePositionDouble(glm::dvec3(0.0, 0.0, 2.0) * deltaTime);
		if(Input::isKeyHold(GLFW_KEY_D)) camera.movePositionDouble(glm::dvec3(2.0, 0.0, 0.0) * deltaTime);
		if(Input::isKeyHold(GLFW_KEY_A)) camera.movePositionDouble(glm::dvec3(-2.0, 0.0, 0.0) * deltaTime);
		
		if(Input::isKeyPressed(GLFW_KEY_T)) level.rotateLayer(0);

		player.update(deltaTime);
		player.draw(camera, lighting);

		level.update(deltaTime);
		level.draw(camera, lighting);

		text.draw();

		if(Input::isKeyHold(GLFW_KEY_E)) angle += 2.0f * deltaTime;
		if(Input::isKeyHold(GLFW_KEY_R)) angle2 += 2.0f * deltaTime;
	}

	textExit();
	audioExit();
	windowExit();

	exit(EXIT_SUCCESS);
}
