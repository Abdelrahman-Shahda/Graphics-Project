#ifndef GRAPHICSPROJECT_PLAY_STATE_HPP
#define GRAPHICSPROJECT_PLAY_STATE_HPP

#include <application.hpp>
#include "game_state.hpp"
#include <../inc/resources/shader.hpp>
#include <../inc/components/flyCameraController.hpp>
#include "../inc/components/camera.hpp"
#include"../inc/components/transform.h"
#include<systems/renderingSystem.hpp>
#include"../inc/entity.hpp"
#include <memory>
#include<utils/mesh-utils.hpp>



class play_state : public game_state {
public:
    std::vector <shared_ptr<Entity>> world;
    RenderingSystem rs;

    Resources::ShaderProgram program;
    shared_ptr<Mesh> meshPtr1=nullptr;
    shared_ptr<Mesh> meshPtr2=nullptr; ////////should be initialized
    void onEnter() {

        program.create();
        program.attach("assets/shaders/ex11_transformation/transform.vert", GL_VERTEX_SHADER);
        program.attach("assets/shaders/ex11_transformation/tint.frag", GL_FRAGMENT_SHADER);
        program.link();
        shared_ptr<Entity> entity1(new Entity);

        MeshUtils::Cuboid(*meshPtr1, true);
        MeshUtils::Sphere(*meshPtr2);





        entity1->addComp<Transform,glm::vec3,glm::vec3,glm::vec3>({0, -1, 0},{glm::pi<float>()/4, glm::pi<float>()/4, 0},{7, 2,  7});
        entity1->addComp<Camera>();
        ///////////entity->addComp<FlyCameraController>();
        ////////////////mesh 3arfa a path el application
        world.push_back(entity1);



        shared_ptr<Entity> entity2(new Entity);
        shared_ptr<Entity> entity3(new Entity);
        entity2->addComp<MeshRenderer,shared_ptr<Mesh>>(meshPtr1);
        entity3->addComp<MeshRenderer,shared_ptr<Mesh>>(meshPtr2);
        entity2->addComp<Transform,glm::vec3,glm::vec3,glm::vec3>({0, -1, 0},{0, 0,  0},{7, 2,  7});
        entity3->addComp<Transform,glm::vec3,glm::vec3,glm::vec3>({0, -1, 0},{0, 0,  0},{7, 2,  7});
        world.push_back(entity2);
        world.push_back(entity3);




        glClearColor(0, 0, 0, 0);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);

        glClearColor(0, 0, 0, 1);


        //glfwGetFramebufferSize(window, &width, &height);
      //  std::shared_ptr<Entity> sptr();
       // std::weak_ptr<Entity> weakPtr = sptr;
       // Transform (  weakPtr,{0, -1, 0},{0, 0,  0},{7, 2,  7});

    }
    void onDraw1(){
         rs.Run(world);

    }
    void onExit(){
        program.destroy();
    }
};
#endif