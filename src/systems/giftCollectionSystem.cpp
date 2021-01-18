#include <systems/giftCollectionSystem.h>

GiftCollectionSystem:: GiftCollectionSystem(const std::shared_ptr<Entity> player_) :player(player_)
{
}

void GiftCollectionSystem::Run(const std::vector<std::shared_ptr<Entity>> &enitities, double delta_time, gameSettings cameraSettings, std::shared_ptr<Entity> skyLight)
{
    std::vector<std::shared_ptr<Entity>> gifts = getEntitiesWithComponent<Gift>(enitities);
    std::shared_ptr<Player> playerComp = player->getComp<Player>();

    for (int i = 0; i < gifts.size(); i++) {
        std::shared_ptr<Gift> giftComp = gifts[i]->getComp<Gift>();
        if (detectCollision(player, gifts[i]) && gifts[i]->getComp<RenderState>()->isVisible == true) {
            gifts[i]->getComp<RenderState>()->isVisible = false;
            int giftScore = gifts[i]->getComp<Gift>()->getPoints();
            playerComp->incrementScore(giftScore);
        }
    }
}