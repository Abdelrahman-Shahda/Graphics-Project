#include <inc/systems/collisionDetectionSystem.h>

bool  CollisionDetectionSystem::areCoordinatesColliding(int min1, int min2, int max2)
{
	if (min1 > min2 && min1 < max2)
		return true;
	return false;
}


/*Detects collision between two objects*/
bool CollisionDetectionSystem::detectCollision(const std::shared_ptr<Entity> gameCharacter, const std::shared_ptr<Entity> gameObject)
{
	//Getting Bounding box coordinates for each entity
	std::shared_ptr<MeshRenderer> meshRender1=gameCharacter->getComp<MeshRenderer>();
	std::shared_ptr<MeshRenderer> meshRender2 = gameObject->getComp<MeshRenderer>();

	glm::vec3 minBoundingBox1 = meshRender1->getMinBoundingBox();
	glm::vec3 minBoundingBox2 = meshRender2->getMinBoundingBox();

	glm::vec3 maxBoundingBox1 = meshRender1->getMaxBoundingBox();
	glm::vec3 maxBoundingBox2 = meshRender2->getMaxBoundingBox();

	//Comparing coordinates to detect collision
	bool collision = areCoordinatesColliding(minBoundingBox1.x, minBoundingBox2.x, maxBoundingBox2.x)
		&& areCoordinatesColliding(minBoundingBox1.y, minBoundingBox2.y, maxBoundingBox2.y)
		&& areCoordinatesColliding(minBoundingBox1.z, minBoundingBox2.z, maxBoundingBox2.z);
	//TODO:: chech if opposite of this is required
	return collision;

}