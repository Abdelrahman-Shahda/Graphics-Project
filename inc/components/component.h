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
	RENDERSTATE,
	COUNT,
} ComponentType;


class Entity;
class Component
{
public:
	Component(std::weak_ptr<Entity> entity);
	ComponentType getType();
	std::shared_ptr<Entity> getEntity();
	virtual ~Component();

protected:
	ComponentType type;
	std::weak_ptr<Entity> entity;

};

#endif /*COMPONENT___H*/