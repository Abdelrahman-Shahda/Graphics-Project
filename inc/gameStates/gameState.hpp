//
// Created by Shaimaa on 11/29/2020.
//

#ifndef GRAPHICSPROJECT_GAME_STATE_HPP
#define GRAPHICSPROJECT_GAME_STATE_HPP

#include <memory>
#include <systems/system.hpp>
#include<entity.hpp>

class Application;

class GameState {
protected:
	Application* applicationPtr;
	std::vector <shared_ptr<Entity>> world;
	std::vector<shared_ptr<System>> systems;

public:
	GameState(Application * applicationPtr) : applicationPtr(applicationPtr) {};
    virtual void onEnter()=0;
    virtual void onDraw(double deltaTime)=0;
    virtual void onExit()=0;
};

#endif //GRAPHICSPROJECT_GAME_STATE_HPP