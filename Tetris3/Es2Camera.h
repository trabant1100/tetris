#pragma once

#include "glm/glm.hpp"

class Es2Camera
{
public:
	Es2Camera(float fovy, float aspectRatio, float near, float far);
	~Es2Camera();
	glm::mat4 GetPerspectiveMatrix() const;
private:
	float fovy;
	float aspectRatio;
	float near;
	float far;
	glm::mat4 perspective;
};

