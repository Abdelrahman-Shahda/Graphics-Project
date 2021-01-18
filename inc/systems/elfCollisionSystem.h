//
// Created by Hania on 1/17/2021.
//

#ifndef GRAPHICSPROJECT_ELFCOLLISIONSYSTEM_H
#define GRAPHICSPROJECT_ELFCOLLISIONSYSTEM_H

#include<systems/collisionDetectionSystem.h>
#include<components/elf.hpp>
#include <components/player.hpp>
#include <time.h>
#include <random>

class elfCollisionSystem :public CollisionDetectionSystem
{
    const std::shared_ptr<Entity> player;

public:
    elfCollisionSystem(const std::shared_ptr<Entity> player_):player(player_)
    {}
	void moveElf(shared_ptr<Entity> elf_entity, double delta_time);
	void Run(const std::vector<std::shared_ptr<Entity>> &enitities, double delta_time, gameSettings cameraSettings, std::shared_ptr<Entity> skyLight) override;
};
#endif //GRAPHICSPROJECT_ELFCOLLISIONSYSTEM_H
