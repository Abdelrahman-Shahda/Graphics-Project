#ifndef GRAPHICSPROJECT_PLAY_STATE_HPP
#define GRAPHICSPROJECT_PLAY_STATE_HPP

#include <gameStates/gameState.hpp>
#include <stateManager.h>
#include<utils/mesh-utils.hpp>

#include<systems/renderingSystem.hpp>
#include <systems/giftCollectionSystem.h>

#include <components/flyCameraController.hpp>
#include <components/camera.hpp>
#include <components/transform.h>
#include <components/lighting.h>
#include <components/player.hpp>
#include <components/gift.hpp>

#include <resources/material.h>
#include <resources/shader.hpp>
#include <resources/texture.h>
#include <resources/sampler.h>

#include <utils/sceneLoader.h>

class PlayState : public GameState {
protected:
	std::shared_ptr<Entity> mainChar;
	std::shared_ptr<Entity> mainCamera;
	int charOrientation;
	gameSettings gameSettings;
	void intializeGameSettings();
public:
	PlayState(StateManagerApplication* app) :GameState(app) {};
	void onEnter() override;
	void onDraw(double deltaTime) override;
    void onExit() override {}
	void moveChar(double deltaTime);
	bool checkGameOver();
	void updateLives();
	std::vector<std::shared_ptr<Entity>> getEntitiesWithTag(const std::vector<std::shared_ptr<Entity>> &entities,std::string tag);
};
#endif