#include "Es2Gfx.h"
#include <stdio.h>
#include "glm/glm.hpp"

Es2Gfx::Es2Gfx()
{
	if (glfwInit() != GL_TRUE)
	{
		throw "GLFW init failed!";
	}

	//if (glfwOpenWindow(640, 480, 8, 8, 8, 8, 16, 0, GLFW_WINDOW) != GL_TRUE)
	if ((window = glfwCreateWindow(640, 480, "TetJS", NULL, NULL)) == NULL)
	{
		throw "GLFW OpenWindow failed!";
	}

	camera = new Es2Camera(45, 4 / 3, 0.01f, 10.0f);
}


Es2Gfx::~Es2Gfx()
{
	glfwTerminate();
	delete camera;
}

void Es2Gfx::BeginPaint()
{
	programObject = InitProgram(camera->GetPerspectiveMatrix());
	assert(programObject);

	// scratch
#define A  -1.0f, 1.0f, 0.5f 
#define B  1.0f, 1.0f, 0.5f
#define C  1.0f, -1.0f, 0.5f 
#define D  -1.0f, -1.0f, 0.5f 

	GLfloat vVertices[] = {
		D, C, A,  B
	};

	GLuint vertexPosObject;
	glGenBuffers(1, &vertexPosObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexPosObject);
	glBufferData(GL_ARRAY_BUFFER, 12 * 4, vVertices, GL_STATIC_DRAW);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(programObject);
	GLuint matrixId = glGetUniformLocation(programObject, "mvp");
	printf("matrixId = %d\n", matrixId);
	glm::mat4 mvp = camera->GetPerspectiveMatrix();
	glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, vertexPosObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Es2Gfx::EndPaint()
{
	glfwSwapBuffers(window);
}

void Es2Gfx::DrawRectangle(int x, int y, int width, int height)
{
	printf("DrawRect");
}

void Es2Gfx::DrawPiece(int x, int y, int width, int height, int color)
{
	printf("DrawRect");
}

void Es2Gfx::DrawScore(int x, int y, int score)
{
	printf("DrawRect");
}
