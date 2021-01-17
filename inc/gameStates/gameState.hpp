//
// Created by Shaimaa on 11/29/2020.
//

#ifndef GRAPHICSPROJECT_GAME_STATE_HPP
#define GRAPHICSPROJECT_GAME_STATE_HPP

#include <memory>
#include <systems/system.hpp>
#include<entity.hpp>

class StateManagerApplication;

class GameState {
protected:
    int current;
	StateManagerApplication* applicationPtr;
	std::vector <shared_ptr<Entity>> world;
	std::vector<shared_ptr<System>> systems;
    shared_ptr<Entity> skyLight = NULL;
	gameSettings gameSettings;

	void intializeGameSettings()
	{
			gameSettings.gameSensitivity = 1.0f;
			gameSettings.jumpAmount = 500;
			gameSettings.friction = 4.0f;
			gameSettings.gravity = 98.0f;
			gameSettings.groundLevel = 0;
			gameSettings.planeLevel = 10;
			gameSettings.ceilLevel = 30;
			gameSettings.rightBound = 50;
			gameSettings.leftBound = -50;
			gameSettings.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
			gameSettings.cameraZoom = false;
			gameSettings.cameraRotate = false;
			gameSettings.cameraPan = false;
			gameSettings.spawnPosition = { 0,10,35 };
			gameSettings.characterRotation = 0.0f;

	}

public:
	GameState(StateManagerApplication * applicationPtr) : applicationPtr(applicationPtr) {};
    int  getcurrent(){return current;}
    void setcurrent(int c){  current=c;}
    virtual void onEnter()=0;
    virtual void onDraw(double deltaTime)=0;
    virtual void onExit()=0;
};

#endif //GRAPHICSPROJECT_GAME_STATE_HPP
