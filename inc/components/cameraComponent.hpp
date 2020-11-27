#ifndef _CAMERACOMPONENT_HPP
#define _CAMERACOMPONENT_HPP

#include <glm/glm.hpp>

#include "component.hpp"

typedef enum{PERSPECTIVE,ORTHOGRAPHIC} CameraType;

class CameraComponent : public Component
{
public:
	CameraComponent(Entity* entity,CameraType cameraType, glm::vec3 cp = { 0, 0, 0 }, glm::vec3 cd = { 0, 0, -1 }) 
		: Component(entity), cameraOffset(cp), cameraDirection(cd)
	{
		type = CAMERA;
		dirty = true;
		Init(cp, cd);
	}
	void Init(glm::vec3 cp, glm::vec3 cd)
	{
		cameraDistance = glm::length(cp);
		yaw = lib::DegToRadf(180);
		if (cp.y != 0)
		{
			pitch = atanf(cp.z / cp.y);
		}
		else
		{
			pitch = 0;
		}
	}
	glm::vec3 cameraOffset;
	glm::vec3 cameraDirection;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	glm::mat4 view;
	bool dirty;
	float pitch;
	float yaw;
	float cameraDistance;
};
#endif // !_CAMERACOMPONENT_HPP
