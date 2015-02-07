#include "Es2Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "glm/gtc/type_ptr.hpp"


Es2Camera::Es2Camera(float fovy, float aspectRatio, float near, float far)
	:fovy(fovy), aspectRatio(aspectRatio), near(near), far(far)
{
	float fovyRad = fovy * (180 / M_PI);
	float f = 1.0f / tan(fovyRad / 2);
	
	// row wise mode
	float persp[16] = {
		(f/aspectRatio), 0, 0, 0,
		0, f, 0, 0,
		0, 0, (far + near) / (near - far), (2 * far * near) / (near - far),
		0, 0, -1, 0
	};

	perspective = glm::transpose(glm::make_mat4(persp));
}

glm::mat4 Es2Camera::GetPerspectiveMatrix() const  {
	return perspective;
}


Es2Camera::~Es2Camera()
{
}
