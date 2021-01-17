#ifndef GIFT__H
#define GIFT__H

#include <components/component.h>

class Gift : public Component
{
private:
	unsigned int points;
public:
	Gift(std::weak_ptr<Entity> entity, int points): Component(entity), points(points){type = GIFT;}
	unsigned int getPoints() { return points; }
};
#endif // !GIFT__H
