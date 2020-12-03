#include <application.hpp>
#include "game_state.hpp"
#include <../inc/resources/shader.hpp>
#include <../inc/components/flyCameraController.hpp>
#include "../inc/components/camera.hpp"
#include"../inc/components/transform.h"
#include"../inc/entity.hpp"
#include <memory>
#ifndef GRAPHICSPROJECT_PLAY_STATE_HPP
#define GRAPHICSPROJECT_PLAY_STATE_HPP

class play_state : public game_state {
public:
    Entity *world = new Entity;
    Resources::ShaderProgram program;
    FlyCameraController main_camera_controller;
    Camera main;
    glm::mat4 ui_camera_matrix;

    void onEnter() {

        program.create();
        program.attach("assets/shaders/ex11_transformation/transform.vert", GL_VERTEX_SHADER);
        program.attach("assets/shaders/ex11_transformation/tint.frag", GL_FRAGMENT_SHADER);
        program.link();
        int width, height;
        //glfwGetFramebufferSize(window, &width, &height);
        std::shared_ptr<Entity> sptr(world);
        std::weak_ptr<Entity> weakPtr = sptr;
        Transform (  weakPtr,{0, -1, 0},
                               {0, 0,  0},
                               {7, 2,  7});

    }
};