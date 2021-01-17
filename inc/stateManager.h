//
// Created by Hania on 1/17/2021.
//

#ifndef GRAPHICSPROJECT_STATEMANAGERAPPLICATION_H
#define GRAPHICSPROJECT_STATEMANAGERAPPLICATION_H

#include<utils/ComponentLookUp.h>
#include<systems/renderingSystem.hpp>
#include<entity.hpp>

#include<gameStates/menuState.hpp>
#include <gameStates/gameState.hpp>
#include <application.hpp>


// Inherting Application class to define our application
class StateManagerApplication : public Application {

    /*******************************************************************************
     *                          Member variables                               *
     *******************************************************************************/
private:

    GameState* next_state = nullptr;
    GameState* current_state = nullptr;

    /*******************************************************************************
     *                          Member functions                               *
     *******************************************************************************/
	WindowConfiguration getWindowConfiguration() override;
	void onInitialize() override;
	void goToState();
	void onDraw(double deltaTime) override;
	void onDestroy() override;

public:
	void setNextState(GameState* next_state_);
};
#endif //GRAPHICSPROJECT_STATEMANAGERAPPLICATION_H
