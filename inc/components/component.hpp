#ifndef COMPONENT___H
#define COMPONENT___H

#include "../entities/entity.hpp"
// Enum that defines all components in ECS
typedef enum{MESH,TRANSFORM} ComponentType;

class Component
{
public:
	ComponentType type;
	Entity* entity;

	Component(Entity* entity);
	virtual ~Component();

};

#endif /*COMPONENT___H*/