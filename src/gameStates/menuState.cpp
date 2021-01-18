//
// Created by shaimaa on 1/15/2021.
//
#include<gameStates/menuState.hpp>



void menuState::onEnter() {
    shared_ptr<RenderingSystem> RS(new RenderingSystem);
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
    shared_ptr<Mesh> skyMesh(new Mesh);

    MeshUtils::Cuboid(*meshPtr1);
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

    shared_ptr<Resources::Texture> menu(new Texture("emissive",ASSETS_DIR"/image/material/menu2.jpg"));
    //shared_ptr<Resources::Texture> restart(new Texture("specular",ASSETS_DIR"/image/material/Restart_.jpg"));
    //shared_ptr<Resources::Texture> exit(new Texture("emissive",ASSETS_DIR"/image/material/exit.jpg"));

    //Material classes
    shared_ptr<Resources::Material> material(new Material(shaderProgram));
    material->addTexture(menu, defaultSampler);
    material->addShaderParameter(skyLightTopColor);
    material->addShaderParameter(skyLightMiddleColor);
    material->addShaderParameter(skyLightBottomColor);




    //Intializing Camera component
    shared_ptr<Entity> mainCamera(new Entity);
    std::shared_ptr<Camera> cameraPtr= mainCamera->addComp<Camera>();
    std::shared_ptr<Transform> transformPtr= mainCamera->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 0, 10, -10 }, {0, 0, 1 }, { 1,1,1 });
    transformPtr->update();
    mainCamera->addComp<FlyCameraController, Application*,std::shared_ptr<Camera>>(applicationPtr,cameraPtr,transformPtr);
    world.push_back(mainCamera);

    //Creating entities
    shared_ptr<Entity> entity2(new Entity);

    entity2->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr1, material);
    entity2->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 0,10, -8}, { 0,0,  3.14/2 }, { 2,2,2});
    entity2->getComp<Transform>()->update();
    entity2->addComp<RenderState,bool>(true);


    world.push_back(entity2);



    this->gameSettings.cameraZoom = false;
    // gameSettings.cameraRotate = false;
    this->gameSettings.cameraPan = false;

}

void menuState::detectchoice(double deltaTime){
    glm::vec2 b2({798,594});
    glm::vec2 b1({481,515});


    if(applicationPtr->getMouse().isPressed(GLFW_MOUSE_BUTTON_LEFT)){

        if(applicationPtr->getMouse().getMousePosition().x>=b1.x&&applicationPtr->getMouse().getMousePosition().x<=b2.x&&applicationPtr->getMouse().getMousePosition().y>=b1.y && applicationPtr->getMouse().getMousePosition().y<=b2.y)
        {
            GameState* nextState = new PlayState(applicationPtr);
            applicationPtr->setNextState(nextState);
        }


    }

}

void menuState::onDraw(double deltaTime) {
    for (auto systemIterator = systems.begin(); systemIterator != systems.end(); systemIterator++) {
        detectchoice(deltaTime);
        (*systemIterator)->Run(world, deltaTime, gameSettings, skyLight);
    }
}

