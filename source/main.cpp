#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "gl.h"
#include "window.h"
#include "settings.h"
#include "dbg.h"

#include "shader.h"
#include "camera.h"
#include "cubes.h"
#include "obj.h"

Settings settings(800, 600);

int main(void)
{
	windowInit();
	glewInit();

	Camera camera(0.001f, 100.0f);

	glViewport(0, 0, settings.width, settings.height);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	float angle = 0.0f;

	Cubes cubes(2);
	Cubes cubes2(2);

	cubes.setPosition(0, glm::vec3(-1.0f, 0.0f, 0.0f));
	cubes.setPosition(1, glm::vec3(1.0f, 0.0f, 0.0f));
	cubes.update();

	cubes2.setPosition(0, glm::vec3(0.0f, -1.0f, 0.0f));
	cubes2.setPosition(1, glm::vec3(0.0f, 1.0f, 0.0f));
	cubes2.update();

	ObjModel obj("test.obj");

	while(windowUpdate())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cubes.model = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
		cubes.draw(camera);
		cubes2.draw(camera);

		obj.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -50.0f)) * glm::rotate(glm::mat4(0.00005f), -angle, glm::vec3(1.0f, 0.0f, 0.0f));
		obj.draw(camera);

		angle = 2.0f * glfwGetTime();
	}

	windowExit();

	exit(EXIT_SUCCESS);
}
