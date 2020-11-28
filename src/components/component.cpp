#include "../../inc/components/component.h"

Component::Component(std::weak_ptr<Entity> entity) :entity(entitity)
{
	this->type = BASE;
}

Component::ComponentType getType()
{
	return this.type;
}

Component::~Component() {}