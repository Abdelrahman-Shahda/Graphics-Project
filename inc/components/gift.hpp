#ifndef GIFT__H
#define GIFT__H

#include <components/component.h>

class Gift : public Component
{
private:
	int points;
public:
	Gift(std::weak_ptr<Entity> entity, int points): Component(entity), points(points){}
};
#endif // !GIFT__H
