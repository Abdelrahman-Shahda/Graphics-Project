#ifndef GRAPHICSPROJECT_PLAY_STATE_HPP
#define GRAPHICSPROJECT_PLAY_STATE_HPP

#include <memory>

#include <gameStates/gameState.hpp>
#include <application.hpp>
#include<entity.hpp>
#include <components/flyCameraController.hpp>
#include <components/camera.hpp>
#include <components/transform.h>
#include<systems/renderingSystem.hpp>
#include<utils/mesh-utils.hpp>
#include <resources/material.h>
#include <resources/shader.hpp>


class PlayState : public GameState {
public:
	PlayState(Application* app) :game_state(app) {};
    std::vector <shared_ptr<Entity>> world;
    RenderingSystem renderingSystem;

	void onEnter();
	void onDraw1();
    void onExit(){
    }
};
#endif