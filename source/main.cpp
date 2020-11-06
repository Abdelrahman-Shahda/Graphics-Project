#include <application.hpp>
#include <shader.hpp>
#include <iostream>
//#include "input/mouse.hpp"


#pragma region helper_functions

// The ingerited class from "Application" to this example.
class ShaderIntroductionApplication : public GraphicsProject::Application {

    // These unsigned integers represent the way we communicate with the GPU.
    // They act like a name (or, in other words, an ID).
    // These uint are passed to the GL header functions to tell the GL which OpenGL object
    // we are referring to. Also the values are set by the GL functions when passed by reference.
    GraphicsProject::ShaderProgram program;
    GLuint vertex_array = 0;
    GraphicsProject::Mouse mouseController;  //To control mouse Actions
    // We need a window with title: "Shader Introduction", size: {1280, 720}, not full screen.
    GraphicsProject::WindowConfiguration getWindowConfiguration() override {
        return { "Shader Introduction", {1280, 720}, false };
    }

    void onInitialize() override {
        program.create();
        program.attach(ASSETS_DIR "/shaders/graphicsproject/screen.vert", GL_VERTEX_SHADER);
        program.attach(ASSETS_DIR "/shaders/Shapes/LetterGShader.frag", GL_FRAGMENT_SHADER);
        program.link();
        mouse.enable(window);                       // Enable mouse events
        glGenVertexArrays(1, &vertex_array);        // Ask GL to create a vertex array to easily create a triangle.

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);       // Set the clear color
    }

    void onDraw(double deltaTime) override {
        glClear(GL_COLOR_BUFFER_BIT);               // Clear the frame buffer (back buffer of the window)
        glUseProgram(program);                      // Ask GL to use this program for the upcoming operations.
                                                    // Every shader and rendering call after glUseProgram will now use this program object (and the shaders).

        //Get mouse position and set the uniform
        glm::vec2 mousePosition = mouse.getMousePosition();
        GLuint scale_uniform_location = glGetUniformLocation(program, "mousePosition");
        glUniform2f(scale_uniform_location, mousePosition.x, 720-mousePosition.y);
        glBindVertexArray(vertex_array);            // Binding is like selecting which object to use.
                                                    // Note that we need to bind a vertex array to draw
                                                    // Even if that vertex array does not send any data down the pipeline

        // Sends vertices down the pipeline for drawing
        // Parameters:
        // mode (GLenum): what primitives to draw. GL_TRIANGLES will combine each 3 vertices into a triangle.
        // first (GLint): the index of the first vertex to draw. It is useless here since we are not receiving data through the vertex array.
        // count (GLsizei): How many vertices to send to the pipeline. Since we are sending 3 vertices only, only one triangle will be drawn.
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(0);                       // Unbind the buffer.
    }

    void onDestroy() override {
        glDeleteProgram(program);                   // Cleaning up the program we compiled and saved.
        glDeleteVertexArrays(1, &vertex_array);     // Clean up the array we allocated Params: (n: number of vertex array objects, array containing the n addresses of the objects)
    }

};

int main(int argc, char** argv) {
    return ShaderIntroductionApplication().run();
}
