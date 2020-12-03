#include "../../inc/components/component.h"

Component::Component(std::weak_ptr<Entity> e) :entity(e)
{
	this->type = BASE;
}

ComponentType Component::getType()
{
	return this->type;
}

std::shared_ptr<Entity> Component::getEntity()
{
	return this->entity.lock();
}


Component::~Component() {}