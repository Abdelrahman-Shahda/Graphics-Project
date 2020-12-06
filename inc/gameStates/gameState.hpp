//
// Created by Shaimaa on 11/29/2020.
//

#ifndef GRAPHICSPROJECT_GAME_STATE_HPP
#define GRAPHICSPROJECT_GAME_STATE_HPP

class Application;

class GameState {
protected:
	Application* applicationPtr;

public:
	GameState(Application * applicationPtr) : applicationPtr(applicationPtr) {};
    virtual void onEnter()=0;
    virtual void onDraw1()=0;
    virtual void onExit()=0;
};

#endif //GRAPHICSPROJECT_GAME_STATE_HPP
