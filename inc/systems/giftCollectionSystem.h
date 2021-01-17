#ifndef GIFT_DETECTION_SYS
#define GIFT_DETECTION_SYS

#include <systems/collisionDetectionSystem.h>
#include <components/gift.hpp>
#include <components/player.hpp>

class GiftCollectionSystem :public CollisionDetectionSystem
{
	const std::shared_ptr<Entity> player;
	
public:
	GiftCollectionSystem(const std::shared_ptr<Entity>);
	void Run(const std::vector<std::shared_ptr<Entity>> &enitities, double delta_time, gameSettings cameraSettings, std::shared_ptr<Entity> skyLight = NULL) override;

};

#endif // !GIFT_DETECTION_SYS
