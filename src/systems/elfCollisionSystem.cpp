//
// Created by Hania on 1/18/2021.
//
#include <systems/elfCollisionSystem.h>

void elfCollisionSystem::Run(const std::vector<std::shared_ptr<Entity>> &enitities, double delta_time, gameSettings cameraSettings, std::shared_ptr<Entity> skyLight) override {
	std::vector<std::shared_ptr<Entity>> elves = getEntitiesWithComponent<Elf>(enitities);
	std::shared_ptr<Player> playerComp = player->getComp<Player>();

	for (int i = 0; i < elves.size(); i++) {
		std::shared_ptr<Elf> elfComp = elves[i]->getComp<Elf>();

		//checking collision with player first
		if (detectCollision(player, elves[i])) {
			elves[i]->getComp<RenderState>()->isVisible = false;
			playerComp->decrementLives();
		}

		moveElf(elves[i],delta_time);
	}
}


void elfCollisionSystem::moveElf(shared_ptr<Entity> elf_entity, double deltaTime)
{
	const int range_from = 0;
	const int range_to = 3;

	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distr(range_from, range_to);
	int x = distr(generator);
	glm::vec3 position = elf_entity->getComp<Transform>()->get_position()[3];
	if (x == 0) position.z -= ((float)deltaTime * 20);
	if (x == 1) position.z += ((float)deltaTime * 20);
	if (x == 2) position.x += ((float)deltaTime * 20);
	if (x == 3) position.x -= ((float)deltaTime * 20);
	if (position.x > -32.5 && position.x < 32.5 && position.z > -22.2 && position.z < 42.8) {
		elf_entity->getComp<Transform>()->set_position(position);
		elf_entity->getComp<Transform>()->update();
	}
}