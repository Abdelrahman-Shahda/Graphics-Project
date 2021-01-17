#include <systems/giftCollectionSystem.h>

GiftCollectionSystem:: GiftCollectionSystem(const std::shared_ptr<Entity> player_) :player(player_)
{
}

void GiftCollectionSystem::Run(const std::vector<std::shared_ptr<Entity>> &enitities, double delta_time, gameSettings cameraSettings, std::shared_ptr<Entity> skyLight)
{
	std::vector<std::shared_ptr<Entity>> gifts = getEntitiesWithComponent<Gift>(enitities);

	for (int i = 0; i < gifts.size(); i++) {

		if (detectCollision(player, gifts[i])) {
			gifts[i]->getComp<RenderState>()->isVisible = false;
		}
	}
}