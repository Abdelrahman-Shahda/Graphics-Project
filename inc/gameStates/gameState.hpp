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
    int current;
	Application* applicationPtr;
	std::vector <shared_ptr<Entity>> world;
    std::vector <shared_ptr<Entity>> world_menu;
	std::vector<shared_ptr<System>> systems;
    shared_ptr<Entity> skyLight = NULL;
public:
	GameState(Application * applicationPtr) : applicationPtr(applicationPtr) {

	};
    int  getcurrent(){return current;}
    void setcurrent(int c){  current=c;}
    virtual void onEnter()=0;
    virtual void onDraw(double deltaTime)=0;
    virtual void onExit()=0;
};

#endif //GRAPHICSPROJECT_GAME_STATE_HPP
