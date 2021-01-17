//
// Created by Hania on 1/17/2021.
//

#ifndef GRAPHICSPROJECT_ELFCOLLISIONSYSTEM_H
#define GRAPHICSPROJECT_ELFCOLLISIONSYSTEM_H
#include<systems/collisionDetectionSystem.h>
#include<components/elf.hpp>
#include <components/player.hpp>
class elfCollisionSystem :public CollisionDetectionSystem
{
    const std::shared_ptr<Entity> player;

public:
    elfCollisionSystem(const std::shared_ptr<Entity> player_):player(player_)
    {}

    void elfCollisionSystem::Run(const std::vector<std::shared_ptr<Entity>> &enitities, double delta_time, gameSettings cameraSettings, std::shared_ptr<Entity> skyLight) override{
        std::vector<std::shared_ptr<Entity>> elves = getEntitiesWithComponent<Elf>(enitities);
        std::shared_ptr<Player> playerComp = player->getComp<Player>();

        for (int i = 0; i < elves.size(); i++) {
            std::shared_ptr<Elf> elfComp = elves[i]->getComp<Elf>();
            if (detectCollision(player, elves[i])) {
                elves[i]->getComp<RenderState>()->isVisible = false;
                playerComp->decrementLives();
            }
        }
    }

};
#endif //GRAPHICSPROJECT_ELFCOLLISIONSYSTEM_H
