//
// Created by shaimaa on 1/15/2021.
//
#ifndef GRAPHICSPROJECT_MENUSTATE_HPP
#define GRAPHICSPROJECT_MENUSTATE_HPP

#include<gameStates/gameState.hpp>
#include <application.hpp>


#include <gameStates/playState.hpp>

#include <resources/texture.h>
#include <resources/material.h>
#include <resources/shader.hpp>
#include<resources/sampler.h>

#include <components/transform.h>
#include <components/camera.hpp>
#include <components/flyCameraController.hpp>
#include <components/lighting.h>

#include <systems/renderingSystem.hpp>
#include <utils/mesh-utils.hpp>

class menuState : public GameState {

    // Index of the current selected menu item

    // A pointer to the current active game (if any).

    gameSettings gameSettings;

public:
    menuState(Application* app) :GameState(app) {current=0;};

    void onEnter() override;
    void onDraw(double deltaTime) override;
    void onExit() override {}
    void detectchoice(double deltaTime);
};

#endif //GRAPHICSPROJECT_MENUSTATE_HPP
