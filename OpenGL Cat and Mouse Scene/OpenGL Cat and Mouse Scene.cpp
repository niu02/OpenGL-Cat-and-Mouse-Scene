#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "shader.h"
#include "texture.h"
#include "window.h"
#include "ModelViewerCamera.h"
#include "catmodel.h"
#include "floormodel.h"
#include "mouse.h"
#include "plant.h"


#include <iostream>

SCamera Camera;

float move_x = 0.f;
float rotate_cat = 0.f;

void processKeyboard(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	bool cam_changed = false;
	float x = 0.f, y = 0.f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		x = 0.f;
		y = -3.f;
		cam_changed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		x = 0.f;
		y = 3.f;
		cam_changed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		x = -3.f;
		y = 0.f;
		cam_changed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		x = 3.f;
		y = 0.f;
		cam_changed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		cam_dist -= 0.3 * Camera.MovementSpeed;
		cam_changed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		cam_dist += 0.3 * Camera.MovementSpeed;
		cam_changed = true;
	}
	if (cam_changed)
	{
		MoveAndOrientCamera(Camera, glm::vec3(0, 0, 0), cam_dist, x, y);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)		move_x -= 0.1;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)		move_x += 0.1;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)		rotate_cat -= 2.0;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)		rotate_cat += 2.0;

}





int main(int argc, char** argv)
{
	GLFWwindow* window = CreateGLFWWindow(800, 600, "Assessment 3");

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


	unsigned int shaderProgram = LoadShader("vs.vert", "fs.frag");

	InitCamera(Camera, 100, 20);
	MoveAndOrientCamera(Camera, glm::vec3(0, 0, 0), cam_dist, 0.f, 0.f);

	GLuint texture1 = setup_texture("woodfloor.bmp");
	GLuint texture2 = setup_texture("fur.bmp");
	GLuint texture3 = setup_texture("plant.bmp");

	unsigned int VAO[4];
	glGenVertexArrays(4, VAO);
	unsigned int VBO[4];
	glGenBuffers(4, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cat), cat, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(floormodel), floormodel, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mouse), mouse, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(VAO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plant), plant, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);

	glUseProgram(shaderProgram);


	while (!glfwWindowShouldClose(window))
	{
		processKeyboard(window);

		glClearColor(0.254f, 0.16f, 0.121f, 1.f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		//cat model
		glm::mat4 cat = glm::mat4(1.f);
		cat = glm::translate(cat, glm::vec3(7.0f, 7.1f, 0.0f));
		cat = glm::rotate(cat, glm::radians(-55.f + rotate_cat), glm::vec3(0.f, 1.f, 0.f));
		int mloc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(cat));
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 1000);

		//floor model
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUseProgram(shaderProgram);
		glm::mat4 floormodel = glm::mat4(1.f);
		mloc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(floormodel));
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 1000);

		//mouse model
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUseProgram(shaderProgram);
		glm::mat4 mouse = glm::mat4(1.f);
		mouse = glm::translate(mouse, glm::vec3(-1.0f + move_x, -4.7f, 4.0f));
		mouse = glm::rotate(mouse, (float)glfwGetTime() / float(0.5), glm::vec3(0.f, -1.f, 0.f));
		mloc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(mouse));
		glBindVertexArray(VAO[2]);
		glDrawArrays(GL_TRIANGLES, 0, 1000);

		//plant model
		glBindTexture(GL_TEXTURE_2D, texture3);
		glUseProgram(shaderProgram);
		glm::mat4 plant = glm::mat4(1.f);
		plant = glm::scale(plant, glm::vec3(1.8f, 1.8f, 1.8f));
		plant = glm::translate(plant, glm::vec3(-4.0f, -0.7f, -2.0f));
		plant = glm::rotate(plant, glm::radians(25.f), glm::vec3(0.f, 1.f, 0.f));
		mloc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(plant));
		glBindVertexArray(VAO[3]);
		glDrawArrays(GL_TRIANGLES, 0, 1000);


		//view matrix
		glm::mat4 view = glm::mat4(1.f);
		view = glm::lookAt(Camera.Position, Camera.Position + Camera.Front, Camera.Up);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

		//projection matrix
		glm::mat4 projection = glm::mat4(1.f);
		projection = glm::perspective(glm::radians(70.f), (float)800 / (float)600, 1.0f, 100.f);
		int ploc = glGetUniformLocation(shaderProgram, "projection");
		glUniformMatrix4fv(ploc, 1, GL_FALSE, glm::value_ptr(projection));


		glBindVertexArray(0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

