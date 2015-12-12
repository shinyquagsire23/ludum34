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
	  {1, 0, 0, 0, 0, 0, 0, 0, 0},  
	  {1, 0, 0, 0, 0, 0, 0, 0, 0}, 
	  {1, 0, 0, 0, 0, 0, 0, 0, 0}, 
	  {1, 0, 0, 0, 0, 0, 0, 0, 0}, 
	  {1, 1, 0, 0, 0, 0, 0, 0, 0}, 
	  {1, 0, 0, 0, 1, 0, 0, 0, 0}, 
	  {1, 0, 0, 0, 0, 0, 0, 0, 0}, 
	  {1, 0, 0, 0, 0, 0, 0, 0, 0}, 
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

	// lighting.setLightPosition(0, glm::vec3(-0.148422, 0.529210, -0.835409));
	lighting.setLightPosition(0, glm::vec3(0.575778, 0.324158, -0.750601));
	lighting.setLightEnabled(0, true);
	lighting.setLightDirectional(0, true);
	lighting.setLightFresnel(0, 0.0f);
	lighting.setLightShininess(0, 3.0f);

	glLineWidth(4.0f);

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

	LevelGeneratorStatic levelGenerator;
	Level level(levelGenerator);
	Cubes lightcube(1);

	double lastFrame = glfwGetTime();

	// Sound sound("drumloop.wav");

	// sound.play();

	glClearColor(0.90f, 0.90f, 0.90f, 1.0f);

	while(windowUpdate())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		double currentFrame = glfwGetTime();
		double deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if(Input::isKeyHold(GLFW_KEY_Y)) lighting.setLightPosition(0, lighting.getLightPosition(0) + glm::vec3(2.0, 0.0, 0.0) * float(deltaTime));
		if(Input::isKeyHold(GLFW_KEY_H)) lighting.setLightPosition(0, lighting.getLightPosition(0) - glm::vec3(2.0, 0.0, 0.0) * float(deltaTime));
		if(Input::isKeyHold(GLFW_KEY_U)) lighting.setLightPosition(0, lighting.getLightPosition(0) + glm::vec3(0.0, 2.0, 0.0) * float(deltaTime));
		if(Input::isKeyHold(GLFW_KEY_J)) lighting.setLightPosition(0, lighting.getLightPosition(0) - glm::vec3(0.0, 2.0, 0.0) * float(deltaTime));
		if(Input::isKeyHold(GLFW_KEY_I)) lighting.setLightPosition(0, lighting.getLightPosition(0) + glm::vec3(0.0, 0.0, 2.0) * float(deltaTime));
		if(Input::isKeyHold(GLFW_KEY_K)) lighting.setLightPosition(0, lighting.getLightPosition(0) - glm::vec3(0.0, 0.0, 2.0) * float(deltaTime));

		if(Input::isKeyHold(GLFW_KEY_E)) angle += 2.0f * deltaTime;
		if(Input::isKeyHold(GLFW_KEY_R)) angle2 += 2.0f * deltaTime;

		if(Input::isKeyPressed(GLFW_KEY_T)) level.rotateLayer(0);

		lighting.setLightPosition(0, glm::normalize(lighting.getLightPosition(0)));

		// std::cout << glm::to_string(lighting.getLightPosition(0)) << std::endl;
		
		{
			level.update(deltaTime);
			player.update(level, deltaTime);
			player.updateCamera(camera);
		}

		{
			lightcube.model = glm::translate(glm::mat4(1.0f), lighting.getLightPosition(0)) * glm::mat4(glm::mat3(0.1f));
			lightcube.draw(camera, lighting);

			level.draw(camera, lighting);

			player.draw(camera, lighting, true);
			player.draw(camera, lighting);

			// text.draw();
		}
	}

	textExit();
	audioExit();
	windowExit();

	exit(EXIT_SUCCESS);
}
