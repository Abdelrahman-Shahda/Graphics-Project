#ifndef COMPONENT___H
#define COMPONENT___H

#include "../entities/entity.hpp"
#include <memory>
// Enum that defines all components in ECS
typedef enum{BASE, MESH,TRANSFORM,CAMERA, COUNT} ComponentType;

class Component
{
public:
	ComponentType type;
	std::weak_ptr<Entity> entity;

	Component(std::weak_ptr<Entity> entity);
	virtual ~Component();

};

#endif /*COMPONENT___H*/