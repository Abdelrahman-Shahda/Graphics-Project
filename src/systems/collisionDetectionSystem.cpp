#include <systems/collisionDetectionSystem.h>
#include <glm/gtx/string_cast.hpp>
bool  CollisionDetectionSystem::areCoordinatesColliding(int min1,int max1, int min2, int max2)
{
	if (max1 > min2 && min1 < max2)
		return true;
	return false;
}


/*Detects collision between two objects*/
bool CollisionDetectionSystem::detectCollision(const std::shared_ptr<Entity> gameCharacter, const std::shared_ptr<Entity> gameObject)
{
	//Getting Bounding box coordinates for each entity
	std::shared_ptr<MeshRenderer> meshRender1 = gameCharacter->getComp<MeshRenderer>();
	std::shared_ptr<MeshRenderer> meshRender2 = gameObject->getComp<MeshRenderer>();
	glm::vec4 minBoundingBox1 = gameCharacter->getComp<Transform>()->get_ModalMatrix() * glm::vec4(meshRender1->getMinBoundingBox(), 1.0);
	glm::vec4 minBoundingBox2 = gameObject->getComp<Transform>()->get_ModalMatrix()* glm::vec4(meshRender2->getMinBoundingBox(), 1.0);

	glm::vec4 maxBoundingBox1 = gameCharacter->getComp<Transform>()->get_ModalMatrix() * glm::vec4(meshRender1->getMaxBoundingBox(), 1.0);
	glm::vec4 maxBoundingBox2 = gameObject->getComp<Transform>()->get_ModalMatrix() * glm::vec4(meshRender2->getMaxBoundingBox(), 1.0);

	/*
	return (areCoordinatesColliding(minBoundingBox1.x, maxBoundingBox1.x, minBoundingBox2.x, maxBoundingBox2.x) &&
		areCoordinatesColliding(minBoundingBox1.y, maxBoundingBox1.y, minBoundingBox2.y, maxBoundingBox2.y) &&
		areCoordinatesColliding(minBoundingBox1.z, maxBoundingBox1.z, minBoundingBox2.z, maxBoundingBox2.z))
	||
		*/
	
		//Comparing coordinates to detect collision
    return(
            maxBoundingBox1.x > minBoundingBox2.x &&
            minBoundingBox1.x < maxBoundingBox2.x &&
            maxBoundingBox1.y > minBoundingBox2.y &&
            minBoundingBox1.y < maxBoundingBox2.y &&
            maxBoundingBox1.z > minBoundingBox2.z &&
            minBoundingBox1.z < maxBoundingBox2.z )||
            (
                    maxBoundingBox1.x > maxBoundingBox2.x &&
                    minBoundingBox1.x < minBoundingBox2.x &&
                    maxBoundingBox1.y > maxBoundingBox2.y &&
                    minBoundingBox1.y < minBoundingBox2.y &&
                    maxBoundingBox1.z > maxBoundingBox2.z &&
                    minBoundingBox1.z < minBoundingBox2.z
                    );

}
