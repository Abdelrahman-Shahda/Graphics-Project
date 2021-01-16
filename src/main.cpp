#include <application.hpp>
#include <resources/shader.hpp>
#include <iostream>
#include <entity.hpp>
#include <systems/renderingSystem.hpp>
#include<gameStates/playState.hpp>
#include <utils/ComponentLookUp.h>
#include<gameStates/menuState.hpp>
#pragma region helper_functions

// Inherting Application class to define our application
class StateManagerApplication : public Application {

	/*******************************************************************************
	 *                          Member variables                               *
	 *******************************************************************************/  
private:
	GameState* next_state = nullptr;
	GameState* current_state = nullptr;
	//PlayState* playstate = nullptr;

	/*******************************************************************************
	 *                          Member functions                               *
	 *******************************************************************************/
	void goToState(GameState* g) {
		next_state = g;
		if (current_state != nullptr) {
			current_state->onExit();

			current_state = next_state;
			next_state = nullptr;
			current_state->onEnter();

		}
	}
    WindowConfiguration getWindowConfiguration() override {
		// Defining an unresizable window of resolution 1280*720
        return { "Game Engine xx", {1280, 720}, false };
    }

    void onInitialize() override {
        current_state=new PlayState(static_cast<Application*>(this));
       ComponentLookUp::setUpMap();
		current_state->onEnter();
    }

	
	void onDraw(double deltaTime) override {
		//Draw Current state
		if (current_state != nullptr) {
			current_state->onDraw(deltaTime);
		}	
	}

    void onDestroy() override {
        delete current_state;
    }

};

int main(int argc, char** argv) {
    return StateManagerApplication().run();
}
