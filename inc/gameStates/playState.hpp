#ifndef GRAPHICSPROJECT_PLAY_STATE_HPP
#define GRAPHICSPROJECT_PLAY_STATE_HPP

#include <gameStates/gameState.hpp>
#include <application.hpp>
#include<systems/renderingSystem.hpp>
#include<utils/mesh-utils.hpp>

#include <components/flyCameraController.hpp>
#include <components/camera.hpp>
#include <components/transform.h>
#include <components/lighting.h>

#include <resources/material.h>
#include <resources/shader.hpp>
#include <resources/texture.h>
#include <resources/sampler.h>

class PlayState : public GameState {
public:
	PlayState(Application* app) :GameState(app) {};
    
	void onEnter() override;
	void onDraw(double deltaTime) override;
    void onExit() override {
    }
};
#endif