#ifndef COLLISION_DS_I
#define COLLISION_DS_I

#include <systems/system.hpp>

class CollisionDetectionSystem : public System
{
private:
	bool areCoordinatesColliding(int min1, int max1, int min2, int max2);
protected:
	bool detectCollision(const std::shared_ptr<Entity> gameCharacter, const std::shared_ptr<Entity> gameObject);
};

#endif // !COLLISION_DS_I
