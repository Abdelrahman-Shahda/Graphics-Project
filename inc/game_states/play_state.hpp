#ifndef GRAPHICSPROJECT_PLAY_STATE_HPP
#define GRAPHICSPROJECT_PLAY_STATE_HPP

#include <application.hpp>
#include "game_state.hpp"
#include <../inc/resources/shader.hpp>
#include <../inc/components/flyCameraController.hpp>
#include "../inc/components/camera.hpp"
#include"../inc/components/transform.h"
#include<systems/renderingSystem.hpp>
#include"../inc/entity.hpp"
#include <memory>
#include<utils/mesh-utils.hpp>
#include <resources/material.h>


class play_state : public game_state {
public:
	play_state(Application* app) :game_state(app) {};
    std::vector <shared_ptr<Entity>> world;
    RenderingSystem renderingSystem;

	void onEnter();
	void onDraw1();
    void onExit(){
    }
};
#endif