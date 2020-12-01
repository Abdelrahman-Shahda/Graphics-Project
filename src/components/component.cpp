#include <components/component.h>

Component::Component(std::weak_ptr<Entity> e) :entity(e)
{
	this->type = BASE;
}

ComponentType Component::getType()
{
	return this->type;
}

Component::~Component() {}