#include <application.hpp>
#include <../inc/resources/shader.hpp>
#include <iostream>
#include "../inc/entity.hpp"
#include <systems/renderingSystem.hpp>
#include<game_states/play_state.hpp>
#pragma region helper_functions

// Inherting Application class to define our application
class ShapeDrawingApplication : public Application {

private:


	/*******************************************************************************
	 *                          Member variables                               *
	 *******************************************************************************/
    //Defining 5 shader programs for out shapes

    //GLuint vertex_array = 0;
   // int state = 0;

   // Resources::ShaderProgram program;
    play_state * playState;


	/*******************************************************************************
	 *                          Member functions                               *
	 *******************************************************************************/
    WindowConfiguration getWindowConfiguration() override {
		// Defining an unresizable window of resolution 1280*720
        return { "Project Phase 1", {1280, 720}, false };
    }

    void onInitialize() override {
        playState=new play_state(static_cast<Application*>(this));
		playState->onEnter();
		current_state = playState;


        /*
		//Intializing shader programs
		for (int i = 0; i < 5; i++)
		{
			program[i].create();
			program[i].attach(ASSETS_DIR "/shaders/screen.vert", GL_VERTEX_SHADER);
		}

        program[0].attach(ASSETS_DIR "/shaders/white.frag", GL_FRAGMENT_SHADER);
		program[1].attach(ASSETS_DIR "/shaders/shapes/SmileyFace.frag", GL_FRAGMENT_SHADER);
		program[2].attach(ASSETS_DIR "/shaders/shapes/HeartShader.frag", GL_FRAGMENT_SHADER);
        program[3].attach(ASSETS_DIR "/shaders/shapes/PacManShader.frag", GL_FRAGMENT_SHADER);
        program[4].attach(ASSETS_DIR "/shaders/shapes/LetterGShader.frag", GL_FRAGMENT_SHADER);

		for(int i=0;i<5;i++)
			program[i].link();

		//Enable mouse & Keyboard events
        mouse.enable(window);                          
        keyboard.enable(window);

		//Creating vertex array 
        glGenVertexArrays(1, &vertex_array);       
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  */

    }

	/*
    void onDraw(double deltaTime) override {

        //goToState(playState);

        /*
        glClear(GL_COLOR_BUFFER_BIT);

		// Use shader program of selected key and get Uniform location
        glUseProgram(program[state]);               
        GLuint scale_uniform_location = glGetUniformLocation(program[state], "mousePosition");

		//Checking pressed key to choose shader program
		if (keyboard.justPressed(GLFW_KEY_1))
			state = 1;
		else if (keyboard.justPressed(GLFW_KEY_2))
			state = 2;
		else if (keyboard.justPressed(GLFW_KEY_3))
			state = 3;
        else if (keyboard.justPressed(GLFW_KEY_4))
          state=4;

        //Get mouse position and set the position uniform
        glm::vec2 mousePosition = mouse.getMousePosition();
        glUniform2f(scale_uniform_location, mousePosition.x, 720-mousePosition.y);

		//Bind the vertices so that we can draw a rectangle covering the whole screen
        glBindVertexArray(vertex_array);            
        glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);    */
    //

    void onDestroy() override {
        delete playState;
    }

};

int main(int argc, char** argv) {
    return ShapeDrawingApplication().run();
}
