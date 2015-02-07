#pragma once
#include "Gfx.h"
#include "Es2Camera.h"
#define GLFW_INCLUDE_ES2 
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

class Es2Gfx :
	public Gfx
{
public:
	Es2Gfx();
	~Es2Gfx();
	void BeginPaint();
	void EndPaint();
	void DrawRectangle(int x, int y, int width, int height);
	void DrawPiece(int x, int y, int width, int height, int color);
	void DrawScore(int x, int y, int score);

private:
	GLFWwindow *window;
	GLuint programObject;
	Es2Camera *camera;
	const GLuint LoadShader(GLenum type, const GLchar *shaderSrc);
	const GLuint InitProgram(glm::mat4 mvp);
};

