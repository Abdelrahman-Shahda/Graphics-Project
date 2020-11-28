#ifndef ENTITY___H
#define ENTITY___H

#include"../../inc/components/component.h"
#include <memory>
#include <vector>

class Entity: public std::enable_shared_from_this<Entity>
{
private:
	std::vector<std::shared_ptr<Component>> components;

public:
	Entity() {};

	//Components Manipulations
	template<class T>
	std::shared_ptr<T> getComponent(COMPONENT_TYPE componentType);

	template<class T>
	bool hasComponent(COMPONENT_TYPE componentType);
	
	template<class T>
	bool addComponent(std::shared_ptr<T>);

	bool removeComponent(std::shared_ptr<Component>);


	~Entity();
	
	
};

template<class T>
std::shared_ptr<T> Entity::getComponent(COMPONENT_TYPE componentType)
{
	for (auto it = components.begin(); it != components.end(); it++)
	{
		if (it->getType() == componentType)
			return it;
	}
	return NULL;
}

template<class T>
bool Entity::hasComponent(COMPONENT_TYPE componentType)
{
	T component = getComponent(componentType);
	if (component)
		return true;

	return false;
}

template<class T>
bool Entity::addComponent()
{
	if(hasComponent<T>(componentT))
}

#endif /*ENTITY___H*/
