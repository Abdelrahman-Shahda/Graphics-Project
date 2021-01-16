#include <systems/collisionDetectionSystem.h>

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

	glm::vec3 minBoundingBox1 = gameCharacter->getComp<Transform>()->get_ModalMatrix() * glm::vec4(meshRender1->getMinBoundingBox(),1.0);
	glm::vec3 minBoundingBox2 = gameObject->getComp<Transform>()->get_ModalMatrix()* glm::vec4( meshRender2->getMinBoundingBox(),1.0);

	glm::vec3 maxBoundingBox1 = gameCharacter->getComp<Transform>()->get_ModalMatrix() * glm::vec4(meshRender1->getMaxBoundingBox(),1.0);
	glm::vec3 maxBoundingBox2 = gameObject->getComp<Transform>()->get_ModalMatrix() * glm::vec4(meshRender2->getMaxBoundingBox(),1.0);

	//Comparing coordinates to detect collision
	bool collision = areCoordinatesColliding(minBoundingBox1.x, minBoundingBox2.x, maxBoundingBox2.x)
		&& areCoordinatesColliding(minBoundingBox1.y, minBoundingBox2.y, maxBoundingBox2.y)
		&& areCoordinatesColliding(minBoundingBox1.z, minBoundingBox2.z, maxBoundingBox2.z);
	//TODO:: chech if opposite of this is required
	return collision;

}

void CollisionDetectionSystem::Run(const std::vector<std::shared_ptr<Entity>> &entities, double delta_time,std::shared_ptr<Entity> skyLight) {

    std::shared_ptr<Entity> mainChar = this->getEntityWithTag(entities,"Santa");
    std::vector<std::shared_ptr<Entity>> gifts = this->getEntitiesWithTag(entities, "Gift");

    for(int i = 0 ; i< gifts.size();i++){
        if(detectCollision(mainChar, gifts[i])){
            gifts[i]->getComp<RenderState>()->isVisible = false;
        }
    }

}