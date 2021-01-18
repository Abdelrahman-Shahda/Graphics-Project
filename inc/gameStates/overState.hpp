//
// Created by Hania on 1/17/2021.
//

#ifndef GRAPHICSPROJECT_OVERSTATE_HPP
#define GRAPHICSPROJECT_OVERSTATE_HPP

#include <gameStates/gameState.hpp>
#include <gameStates/menuState.hpp>

#include <stateManager.h>
#include <application.hpp>

#include<components/camera.hpp>
#include<components/flyCameraController.hpp>
#include <components/transform.h>
#include<components/lighting.h>
#include <stateManager.h>

#include<resources/material.h>
#include <resources/texture.h>
#include<resources/shader.hpp>
#include <resources/sampler.h>

#include <systems/renderingSystem.hpp>
#include <utils/mesh-utils.hpp>
class GameOverState:public GameState{
public:
	GameOverState(StateManagerApplication* app) :GameState(app) {current=0;};
    void onEnter() override{ shared_ptr<RenderingSystem> RS(new RenderingSystem);
        systems.push_back(RS);

        //Intializing resources
        //shaders
        shared_ptr< Resources::ShaderProgram> shaderProgram(new Resources::ShaderProgram);

        //Light shaders
        shaderProgram->create();
        shaderProgram->attach(ASSETS_DIR"/shaders/light_transform.vert", GL_VERTEX_SHADER);
        shaderProgram->attach(ASSETS_DIR "/shaders/light_array.frag", GL_FRAGMENT_SHADER);
        shaderProgram->link();

        //Sky shaders
        shared_ptr< Resources::ShaderProgram> skyProgram(new Resources::ShaderProgram);
        skyProgram->create();
        skyProgram->attach(ASSETS_DIR"/shaders/sky_transform.vert", GL_VERTEX_SHADER);
        skyProgram->attach(ASSETS_DIR "/shaders/sky.frag", GL_FRAGMENT_SHADER);
        skyProgram->link();

        //Meshes
        shared_ptr<Mesh> meshPtr1(new Mesh);
        //shared_ptr<Mesh> meshPtr2(new Mesh);
        //shared_ptr<Mesh> meshPtr3(new Mesh);
        shared_ptr<Mesh> skyMesh(new Mesh);

        MeshUtils::Cuboid(*meshPtr1);
        //MeshUtils::Cuboid(*meshPtr2);
        // MeshUtils::Cuboid(*meshPtr3);
        MeshUtils::Cuboid(*skyMesh);

        //Sky entity
        shared_ptr<Entity> skyTest(new Entity);
        shared_ptr<Resources::Material> skyMaterial(new Material(skyProgram));
        skyTest->addComp<SkyLight, bool, glm::vec3, glm::vec3, glm::vec3>(true, { 0.25, 0.3, 0.5 }, { 0.35, 0.35, 0.4 }, { 0.25, 0.25, 0.25 });
        skyTest->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(skyMesh, skyMaterial);
        skyTest->addComp<RenderState,bool,bool>(true,true);
        skyLight = skyTest;

        //Shader Params
        std::shared_ptr<SkyLight> skyLightComponent = skyLight->getComp<SkyLight>();
        shared_ptr<Resources::ShaderParameter<glm::vec3>> skyLightTopColor(new ShaderParameter<glm::vec3>("sky_light.top_color", skyLightComponent != NULL && skyLightComponent->enabled ? skyLightComponent->top_color : glm::vec3(0.0f)));
        shared_ptr<Resources::ShaderParameter<glm::vec3>> skyLightMiddleColor(new ShaderParameter<glm::vec3>("sky_light.middle_color", skyLightComponent != NULL && skyLightComponent->enabled ? skyLightComponent->middle_color : glm::vec3(0.0f)));
        shared_ptr<Resources::ShaderParameter<glm::vec3>> skyLightBottomColor(new ShaderParameter<glm::vec3>("sky_light.bottom_color", skyLightComponent != NULL && skyLightComponent->enabled ? skyLightComponent->bottom_color : glm::vec3(0.0f)));
        shared_ptr<Resources::ShaderParameter<float>> skyExposure(new ShaderParameter<float>("exposure", 2.0f));

        //Adding parameters to sky light entity
        skyMaterial->addShaderParameter(skyLightTopColor);
        skyMaterial->addShaderParameter(skyLightBottomColor);
        skyMaterial->addShaderParameter(skyLightMiddleColor);
        skyMaterial->addShaderParameter(skyExposure);

        //Textures & Samplers
        shared_ptr<Resources::Sampler> defaultSampler(new Sampler());
        shared_ptr<Resources::Sampler> customizedSampler(new Sampler(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_NEAREST));

        shared_ptr<Resources::Texture> menu(new Texture("emissive",ASSETS_DIR"/image/material/gameover.jpg"));
        //shared_ptr<Resources::Texture> restart(new Texture("specular",ASSETS_DIR"/image/material/Restart_.jpg"));
        //shared_ptr<Resources::Texture> exit(new Texture("emissive",ASSETS_DIR"/image/material/exit.jpg"));

        //Material classes
        shared_ptr<Resources::Material> material(new Material(shaderProgram));
        material->addTexture(menu, defaultSampler);
        material->addTexture(menu, defaultSampler);
        material->addTexture(menu, defaultSampler);
        material->addShaderParameter(skyLightTopColor);
        material->addShaderParameter(skyLightMiddleColor);
        material->addShaderParameter(skyLightBottomColor);


        /*shared_ptr<Resources::Material> material2(new Material(shaderProgram));
        material2->addTexture(restart, customizedSampler);
        material2->addTexture(restart, customizedSampler);
        material2->addTexture(restart, customizedSampler);
        material2->addShaderParameter(skyLightTopColor);
        material2->addShaderParameter(skyLightMiddleColor);
        material2->addShaderParameter(skyLightBottomColor);

        shared_ptr<Resources::Material> material3(new Material(shaderProgram));
        material3->addTexture(exit, defaultSampler);
        material3->addTexture(exit, defaultSampler);
        material3->addTexture(exit, defaultSampler);
        material3->addShaderParameter(skyLightTopColor);
        material3->addShaderParameter(skyLightMiddleColor);
        material3->addShaderParameter(skyLightBottomColor);*/

        //Intializing Camera component
        shared_ptr<Entity> mainCamera(new Entity);
        std::shared_ptr<Camera> cameraPtr= mainCamera->addComp<Camera>();
        std::shared_ptr<Transform> transformPtr= mainCamera->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 0, 10, -10 }, {0, 0, 1 }, { 1,1,1 });
        transformPtr->update();
        mainCamera->addComp<FlyCameraController, Application*,std::shared_ptr<Camera>>(static_cast<Application*>(applicationPtr),cameraPtr,transformPtr);
        world.push_back(mainCamera);

        //Creating entities
        shared_ptr<Entity> entity2(new Entity);
        //  shared_ptr<Entity> entity3(new Entity);
        ///  shared_ptr<Entity> entity4(new Entity);

        entity2->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr1, material);
        entity2->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 0,10, -8}, { 0,0,  3.14/2 }, { 2,2,2});
        entity2->getComp<Transform>()->update();
        entity2->addComp<RenderState,bool,bool>(true,true);



        /*  entity3->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr2, material2);
          entity3->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 0, 10, -7 }, { 0, 0, 3.14/2  }, { 1, 1,  1 });
          entity3->getComp<Transform>()->update();
          entity3->addComp<RenderState,bool>(true);
          entity4->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr3, material3);
          entity4->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 0, 9, -7 }, {0, 0, 3.14/2  }, { 1, 1, 1 });
          entity4->getComp<Transform>()->update();
          entity4->addComp<RenderState>();*/
        world.push_back(entity2);
        //world.push_back(entity3);
        //world.push_back(entity4);


        gameSettings.cameraZoom = false;
        // gameSettings.cameraRotate = false;
        gameSettings.cameraPan = false;
    }
    void  detectchoice(double deltaTime){
        glm::vec2 b2({671,402});
        glm::vec2 b1({604,338});


        if(applicationPtr->getMouse().isPressed(GLFW_MOUSE_BUTTON_LEFT)){
            //std::cout<<applicationPtr->getMouse().getMousePosition().x<<"x coordinates"<<std::endl;
            //std::cout<<applicationPtr->getMouse().getMousePosition().y<<"x coordinates"<<std::endl;


            if(applicationPtr->getMouse().getMousePosition().x>=b1.x&&applicationPtr->getMouse().getMousePosition().x<=b2.x&&applicationPtr->getMouse().getMousePosition().y>=b1.y && applicationPtr->getMouse().getMousePosition().y<=b2.y)
            {
				applicationPtr->setNextState(new menuState(applicationPtr));
            }


        }
    }
    void onDraw(double deltaTime) override
    {
            for (auto systemIterator = systems.begin(); systemIterator != systems.end(); systemIterator++) {
                detectchoice(deltaTime);
                (*systemIterator)->Run(world, deltaTime, gameSettings, skyLight);
            }

        
    }

    void onExit() override{}

};

#endif //GRAPHICSPROJECT_OVERSTATE_HPP
