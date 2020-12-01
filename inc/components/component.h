#ifndef COMPONENT___H
#define COMPONENT___H

#include <memory>

// Enum that defines all components in ECS
typedef enum{
	BASE,
	MESH_RENDERER,
	TRANSFORM,
	CAMERA,
	CAMERACONTROLLER,
	COUNT,
} ComponentType;


class Entity;
class Component
{
public:
	Component(std::weak_ptr<Entity> entity);
	ComponentType getType();
	virtual ~Component();

protected:
	ComponentType type;
	std::weak_ptr<Entity> entity;

};

#endif /*COMPONENT___H*/