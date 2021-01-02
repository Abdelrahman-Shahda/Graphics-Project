#ifndef GRAPHICSPROJECT_PLAY_STATE_HPP
#define GRAPHICSPROJECT_PLAY_STATE_HPP

#include <gameStates/gameState.hpp>
#include <application.hpp>

#include <components/flyCameraController.hpp>
#include <components/camera.hpp>
#include <components/transform.h>
#include<systems/renderingSystem.hpp>
#include<utils/mesh-utils.hpp>
#include <resources/material.h>
#include <resources/shader.hpp>
#include <components/lighting.h>
#include <resources/texture.h>

class PlayState : public GameState {
public:
	PlayState(Application* app) :GameState(app) {};

	void onEnter() override;
	void onDraw(double deltaTime) override;
    void onExit() override {
    }
};
#endif