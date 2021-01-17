//
// Created by Hania on 1/17/2021.
//


#ifndef GRAPHICSPROJECT_STATEMANAGERAPPLICATION_H
#define GRAPHICSPROJECT_STATEMANAGERAPPLICATION_H

#include<utils/ComponentLookUp.h>
#include<systems/renderingSystem.hpp>
#include<entity.hpp>
#include <gameStates/gameState.hpp>
#include<gameStates/overState.hpp>
#include <gameStates/playState.hpp>
#include <gameStates/menuState.hpp>
#include <application.hpp>
void goToState(GameState*next_state,GameState * current_state) {
    if(next_state!=nullptr)
    {
        if (current_state != nullptr) {
            current_state->onExit();
            current_state = next_state;
            next_state = nullptr;
            current_state->onEnter();
    }

    }
}
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
    WindowConfiguration getWindowConfiguration() override {
        // Defining an unresizable window of resolution 1280*720
        return { "Game Engine xx", {1280, 720}, false };
    }

    void onInitialize() override {
        current_state=new menuState(static_cast<Application*>(this));
        ComponentLookUp::setUpMap();
        current_state->onEnter();

    }


    void onDraw(double deltaTime) override {
        //Draw Current state
        if (current_state != nullptr) {
            current_state->onDraw(deltaTime);
            if(current_state->getcurrent()==1){
                next_state=new PlayState(static_cast<Application*>(this));
                goToState(next_state,current_state);
                current_state = next_state;
                current_state->setcurrent(4);
            }
            else if(current_state->getcurrent()==2){
                next_state=new overState(static_cast<Application*>(this));
                goToState(next_state,current_state);
                current_state = next_state;
                current_state->setcurrent(4);
            }

        }

    }

    void onDestroy() override {
        delete current_state;
    }
public:


};
#endif //GRAPHICSPROJECT_STATEMANAGERAPPLICATION_H
