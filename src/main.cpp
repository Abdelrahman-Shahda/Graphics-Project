#include <application.hpp>
#include <resources/shader.hpp>
#include <iostream>
#include <entity.hpp>
#include <systems/renderingSystem.hpp>
#include<gameStates/playState.hpp>
#include<StateManagerApplication.h>
#pragma region helper_functions



int main(int argc, char** argv) {
    return StateManagerApplication().run();
}
