#ifndef COMPONENT___H
#define COMPONENT___H

#include <memory>
#include <components/component.h>

// Enum that defines all components in ECS
typedef enum{
	BASE,
	MESH,
	TRANSFORM,
	CAMERA,
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
	std::weak_ptr<Entity>* entity;

};

#endif /*COMPONENT___H*/