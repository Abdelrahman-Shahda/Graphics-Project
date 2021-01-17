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

    //Meshes
    shared_ptr<Mesh> meshPtr1(new Mesh);
    MeshUtils::Cuboid(*meshPtr1);


    //Textures & Samplers
    shared_ptr<Resources::Sampler> defaultSampler(new Sampler());

    shared_ptr<Resources::Texture> menu(new Texture("albedo",ASSETS_DIR"/image/material/menu2.jpg"));
    //shared_ptr<Resources::Texture> restart(new Texture("specular",ASSETS_DIR"/image/material/Restart_.jpg"));
    //shared_ptr<Resources::Texture> exit(new Texture("emissive",ASSETS_DIR"/image/material/exit.jpg"));

    //Material classes
    shared_ptr<Resources::Material> material(new Material(shaderProgram));
    material->addTexture(menu, defaultSampler);

    //Intializing Camera component
    shared_ptr<Entity> mainCamera(new Entity);
    std::shared_ptr<Camera> cameraPtr= mainCamera->addComp<Camera>();
    std::shared_ptr<Transform> transformPtr= mainCamera->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 0, 10, -10 }, {0, 0, 1 }, { 1,1,1 });
    transformPtr->update();
    mainCamera->addComp<FlyCameraController, Application*,std::shared_ptr<Camera>>(applicationPtr,cameraPtr,transformPtr);
    world.push_back(mainCamera);

    //Creating entities
    shared_ptr<Entity> menuCuboid(new Entity);

	menuCuboid->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr1, material);
	menuCuboid->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 0,10, -8}, { 0,0,  3.14/2 }, { 2,2,2});
	menuCuboid->getComp<Transform>()->update();
	menuCuboid->addComp<RenderState,bool,bool>(true,false);

    world.push_back(menuCuboid);

    gameSettings.cameraZoom = false;
    gameSettings.cameraRotate = false;
    gameSettings.cameraPan = false;

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

