#include <application.hpp>
#include <shader.hpp>
#include <iostream>
//#include "input/mouse.hpp"


#pragma region helper_functions

//Keyboard keys
#define KEY_1	49
#define KEY_2	50
#define KEY_3	51
#define KEY_4	52

// Inherting Application class to define out application
class ShaderIntroductionApplication : public GraphicsProject::Application {

private:
	//
    //Defining 5 shader programs for out shapes
    GraphicsProject::ShaderProgram program[5];
    GLuint vertex_array = 0;
    int state = 0;
    GraphicsProject::Mouse mouseController;  

    // Defining an unresizable window of resolution 1280*720
    GraphicsProject::WindowConfiguration getWindowConfiguration() override {
        return { "Project Phase 1", {1280, 720}, false };
    }

    void onInitialize() override {
		//Intializing shader programs
		for (int i = 0; i < 5; i++)
		{
			program[i].create();
			program[i].attach(ASSETS_DIR "/shaders/graphicsproject/screen.vert", GL_VERTEX_SHADER);
		}

        program[0].attach(ASSETS_DIR "/shaders/graphicsproject/white.frag", GL_FRAGMENT_SHADER);
		program[1].attach(ASSETS_DIR "/shaders/shapes/SmileyFace.frag", GL_FRAGMENT_SHADER);
		program[2].attach(ASSETS_DIR "/shaders/shapes/HeartShader.frag", GL_FRAGMENT_SHADER);
        program[3].attach(ASSETS_DIR "/shaders/shapes/PacManShader.frag", GL_FRAGMENT_SHADER);
        program[4].attach(ASSETS_DIR "/shaders/shapes/LetterGShader.frag", GL_FRAGMENT_SHADER);

		for(int i=0;i<5;i++)
			program[i].link();

        mouse.enable(window);                          //Enable mouse events
        keyboard.enable(window);                       // Enable keyboard events
        glGenVertexArrays(1, &vertex_array);        // Ask GL to create a vertex array to easily create a triangle.
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);       // Set the clear color

    }

    void onDraw(double deltaTime) override {
        glClear(GL_COLOR_BUFFER_BIT);               // Clear the frame buffer (back buffer of the window)
        glUseProgram(program[state]);               // Use shader program of selected key
        GLuint scale_uniform_location = glGetUniformLocation(program[state], "mousePosition");

		//Checking pressed key to choose shader program
		if (keyboard.justPressed(KEY_1))
			state = 1;
		else if (keyboard.justPressed(KEY_2))
			state = 2;
		else if (keyboard.justPressed(KEY_3))
			state = 3;
        else if (keyboard.justPressed(KEY_4))
          state=4;

        //Get mouse position and set the uniform
        glm::vec2 mousePosition = mouse.getMousePosition();
        glUniform2f(scale_uniform_location, mousePosition.x, 720-mousePosition.y);

		//Bind the vertices so that we can draw a rectangle covering the whole screen
        glBindVertexArray(vertex_array);            
        glDrawArrays(GL_TRIANGLES, 0, 6);
       glBindVertexArray(0);                       
    }

    void onDestroy() override {
		//Deleting programs
        for (int i=0; i<5; i++)
			glDeleteProgram(program[i]);     

		//Deleting vertex array used
        glDeleteVertexArrays(1, &vertex_array);    
    }

};

int main(int argc, char** argv) {
    return ShaderIntroductionApplication().run();
}
