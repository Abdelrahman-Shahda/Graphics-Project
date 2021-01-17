//
// Created by Shaimaa on 11/29/2020.
//
#include <gameStates/playState.hpp>
#include <glm/gtx/string_cast.hpp>

void PlayState::onEnter() {

	//Intializing resources
	//shaders
	shared_ptr< Resources::ShaderProgram> shaderProgram(new Resources::ShaderProgram);
	SceneLoader * sceneLoader = new SceneLoader(ASSETS_DIR"/scenes/scene.json");

	world = sceneLoader->loadEntities(applicationPtr);
	skyLight = sceneLoader->loadSky();
//	std::cout<<"Test hena ya hob " <<sceneLoader->loadEntities(applicationPtr).size()<<std::endl;
//	//Light shaders
//	shaderProgram->create();
//	shaderProgram->attach(ASSETS_DIR"/shaders/light_transform.vert", GL_VERTEX_SHADER);
//	shaderProgram->attach(ASSETS_DIR "/shaders/light_array.frag", GL_FRAGMENT_SHADER);
//	shaderProgram->link();
//
//	//Sky shaders
//	shared_ptr< Resources::ShaderProgram> skyProgram(new Resources::ShaderProgram);
//	skyProgram->create();
//	skyProgram->attach(ASSETS_DIR"/shaders/sky_transform.vert", GL_VERTEX_SHADER);
//	skyProgram->attach(ASSETS_DIR "/shaders/sky.frag", GL_FRAGMENT_SHADER);
//	skyProgram->link();
//
//	//Meshes
//	shared_ptr<Mesh> meshPtr(new Mesh);
//	shared_ptr<Mesh> meshPtr2(new Mesh);
//	shared_ptr<Mesh> skyMesh(new Mesh);
//	shared_ptr<Mesh> iceMesh(new Mesh);
//	shared_ptr<Mesh> treeMesh(new Mesh);
//	shared_ptr<Mesh> sleighMesh(new Mesh);
//	shared_ptr<Mesh> heartMesh_1(new Mesh);
//	shared_ptr<Mesh> heartMesh_2(new Mesh);
//	shared_ptr<Mesh> heartMesh_3(new Mesh);
//
//	glm::vec3 min;
//    glm::vec3 max;
//
//	MeshUtils::loadOBJ(*meshPtr,ASSETS_DIR"/models/Santa Claus/santa.obj");
//	MeshUtils::loadOBJ(*treeMesh,ASSETS_DIR"/models/Tree/tree.obj");
//	MeshUtils::loadOBJ(*sleighMesh,ASSETS_DIR"/models/Sleigh/sleigh.obj");
//	MeshUtils::loadOBJ(*heartMesh_1,ASSETS_DIR"/models/Heart/Heart.obj");
//	MeshUtils::loadOBJ(*heartMesh_2,ASSETS_DIR"/models/Heart/Heart.obj");
//	MeshUtils::loadOBJ(*heartMesh_3,ASSETS_DIR"/models/Heart/Heart.obj");
//
//	MeshUtils::Cuboid(*meshPtr2,false);
//    MeshUtils::Plane(*iceMesh,{1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});
////	std::cout <<"Min: x " <<meshPtr->getMinPoint().x << " y "<< meshPtr->getMinPoint().y << " z "<< meshPtr->getMinPoint().z <<std::endl;
////    std::cout <<"Max: x " <<meshPtr->getMaxPoint().x << " y "<< meshPtr->getMaxPoint().y << " z "<< meshPtr->getMaxPoint().z <<std::endl;
//
//
//	MeshUtils::Cuboid(*skyMesh);
//
//	//Sky entity
//	shared_ptr<Entity> skyTest(new Entity);
//	shared_ptr<Resources::Material> skyMaterial(new Material(skyProgram));
//	skyTest->addComp<SkyLight, bool, glm::vec3, glm::vec3, glm::vec3>(true, { 0.1, 0.1, 0.1 }, { 0.35, 0.35, 0.4 }, { 0.25, 0.25, 0.25 });
//	skyTest->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(skyMesh, skyMaterial);
//	skyTest->addComp<RenderState,bool,bool>(true,true);
//	skyLight = skyTest;
//
//	//Shader Params
//	std::shared_ptr<SkyLight> skyLightComponent = skyLight->getComp<SkyLight>();
//	shared_ptr<Resources::ShaderParameter<glm::vec3>> skyLightTopColor(new ShaderParameter<glm::vec3>("sky_light.top_color", skyLightComponent != NULL && skyLightComponent->enabled ? skyLightComponent->top_color : glm::vec3(0.0f)));
//	shared_ptr<Resources::ShaderParameter<glm::vec3>> skyLightMiddleColor(new ShaderParameter<glm::vec3>("sky_light.middle_color", skyLightComponent != NULL && skyLightComponent->enabled ? skyLightComponent->middle_color : glm::vec3(0.0f)));
//	shared_ptr<Resources::ShaderParameter<glm::vec3>> skyLightBottomColor(new ShaderParameter<glm::vec3>("sky_light.bottom_color", skyLightComponent != NULL && skyLightComponent->enabled ? skyLightComponent->bottom_color : glm::vec3(0.0f)));
//	shared_ptr<Resources::ShaderParameter<float>> skyExposure(new ShaderParameter<float>("exposure", 2.0f));
//
//	//Adding parameters to sky light entity
//	skyMaterial->addShaderParameter(skyLightTopColor);
//	skyMaterial->addShaderParameter(skyLightBottomColor);
//	skyMaterial->addShaderParameter(skyLightMiddleColor);
//	skyMaterial->addShaderParameter(skyExposure);
//
//	//Textures & Samplers
//	shared_ptr<Resources::Sampler> defaultSampler(new Sampler());
//	shared_ptr<Resources::Sampler> customizedSampler(new Sampler(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_NEAREST));
//    shared_ptr<Resources::Sampler> iceSampler(new Sampler(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_NEAREST));
//	shared_ptr<Resources::Texture> santaTexture(new Texture("albedo",ASSETS_DIR"/image/material/santa.jpg"));
//	shared_ptr<Resources::Texture> specularTexture(new Texture("specular",ASSETS_DIR"/image/material/santa_spec.jpg"));
//    shared_ptr<Resources::Texture> emissiveTexture(new Texture("emissive",ASSETS_DIR"/image/material/santa.jpg"));
//    shared_ptr<Resources::Texture> iceTexture(new Texture("albedo",ASSETS_DIR"/image/material/ice.jpg"));
//    shared_ptr<Resources::Texture> giftTexture(new Texture("albedo",ASSETS_DIR"/image/material/gift.jpg"));
//	shared_ptr<Resources::Texture> heartTexture(new Texture("albedo",ASSETS_DIR"/image/material/heart.jpg"));
//
//    //Material classes
//	shared_ptr<Resources::Material> material(new Material(shaderProgram));
//	shared_ptr<Resources::Material> heartMaterial(new Material(shaderProgram));
//    shared_ptr<Resources::Material> material2(new Material(shaderProgram));
//
//	heartMaterial->addTexture(heartTexture,customizedSampler);
//
//	material->addTexture(santaTexture, customizedSampler);
//	material->addTexture(specularTexture,customizedSampler);
//	//material2->addTexture(emissiveTexture, customizedSampler);
//	material->addShaderParameter(skyLightTopColor);
//	material->addShaderParameter(skyLightMiddleColor);
//	material->addShaderParameter(skyLightBottomColor);
//
//    material2->addTexture(iceTexture,iceSampler);
//    material2->addShaderParameter(skyLightTopColor);
//    material2->addShaderParameter(skyLightMiddleColor);
//    material2->addShaderParameter(skyLightBottomColor);
//
//	shared_ptr<Resources::Material> giftMaterial(new Material(shaderProgram));
//	giftMaterial->addTexture(giftTexture, customizedSampler);
//	//giftMaterial->addTexture(specularTexture, customizedSampler);
//	giftMaterial->addShaderParameter(skyLightTopColor);
//	giftMaterial->addShaderParameter(skyLightMiddleColor);
//	giftMaterial->addShaderParameter(skyLightBottomColor);
//
//	//Intializing Camera component
//	shared_ptr<Entity> mainCamera(new Entity);
//	std::shared_ptr<Camera> cameraPtr= mainCamera->addComp<Camera>();
//	std::shared_ptr<Transform> camTransformPtr= mainCamera->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 0, 8, -10 }, {0, 0, 1 }, { 1,1,1 });
//	camTransformPtr->update();
//
//	mainCamera->addComp<FlyCameraController, Application*,std::shared_ptr<Camera>>(applicationPtr,cameraPtr,camTransformPtr);
//	world.push_back(mainCamera);
//
//	//Creating entities
//	shared_ptr<Entity> mainChar(new Entity("Santa"));
//	mainChar->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr, material);
//	mainChar->addComp<Player>();
//	std::shared_ptr<Transform> mainTransformPtr= mainChar->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 0, 10, 35}, {0, 3.14, 0 }, { 1, 1, 1 });
//	mainTransformPtr->update();
//    mainChar->addComp<RenderState,bool,bool>(true,true);
//	world.push_back(mainChar);
//
//	    //Make camera follow Main character
//    camTransformPtr->set_parent(mainTransformPtr);
//    mainTransformPtr->add_child(camTransformPtr);
//
//	//gift
//	shared_ptr<Entity> gift(new Entity("Gift"));
//	gift->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr2, giftMaterial);
//	gift->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 0, 10, -12 }, { 0, 0, 0 }, { 1, 1,  1 });
//	gift->getComp<Transform>()->update();
//	gift->addComp<Gift, int>(100);
//    gift->addComp<RenderState,bool>(true);
//	world.push_back(gift);
//
//    //hearts
//	shared_ptr<Entity> heart_1(new Entity("Life"));
//	heart_1->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(heartMesh_1, heartMaterial);
//	heart_1->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ -35, 60, 50 }, { 3*3.14/2,0 , 0 }, { 0.05, 0.05,  0.05 });
//	heart_1->getComp<Transform>()->update();
//    heart_1->addComp<RenderState,bool>(true);
//	world.push_back(heart_1);
//
//	shared_ptr<Entity> heart_2(new Entity("Life"));
//	heart_2->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(heartMesh_2, heartMaterial);
//	heart_2->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ -40, 60, 50 }, { 3*3.14/2, 0, 0 }, { 0.05, 0.05,  0.05 });
//	heart_2->getComp<Transform>()->update();
//    heart_2->addComp<RenderState,bool>(true);
//	world.push_back(heart_2);
//
//	shared_ptr<Entity> heart_3(new Entity("Life"));
//	heart_3->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(heartMesh_3, heartMaterial);
//	heart_3->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ -45, 60, 50 }, { 3*3.14/2,0 , 0 }, { 0.05, 0.05,  0.05 });
//	heart_3->getComp<Transform>()->update();
//    heart_3->addComp<RenderState,bool>(true);
//	world.push_back(heart_3);
//
//	//Make heart follow Main character
//    heart_1->getComp<Transform>()->set_parent(mainTransformPtr);
//    mainTransformPtr->add_child( heart_1->getComp<Transform>());
//	heart_2->getComp<Transform>()->set_parent(mainTransformPtr);
//    mainTransformPtr->add_child( heart_2->getComp<Transform>());
//	heart_3->getComp<Transform>()->set_parent(mainTransformPtr);
//    mainTransformPtr->add_child( heart_3->getComp<Transform>());
//
//	//icePlane
//    shared_ptr<Entity> icePlane(new Entity());
//    icePlane->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(iceMesh, material2);
//    std::shared_ptr<Transform> icePtr= icePlane->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 0, 10, 7.5 }, {0, 0, 0 }, { 60, 1, 60 });
//    icePtr->update();
//    icePlane->addComp<RenderState,bool>(true);
//    world.push_back(icePlane);
//
//	//Tree
//    shared_ptr<Entity> tree(new Entity());
//    tree->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(treeMesh, material2);
//    std::shared_ptr<Transform> treePtr= tree->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ -20, 10, -10 }, {0, 0, 0 }, { 0.1, 0.1, 0.1 });
//    treePtr->update();
//    tree->addComp<RenderState,bool>(true);
//    world.push_back(tree);
//
//     //Santa Sleigh
//	shared_ptr<Entity> sleigh(new Entity());
//    sleigh->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(sleighMesh, material);
//    std::shared_ptr<Transform> sleighPtr= sleigh->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 20, 10, -15 }, {0, 3.14/2, 0 }, { 0.003, 0.003, 0.003 });
//    sleighPtr->update();
//    sleigh->addComp<RenderState,bool>(true);
//    world.push_back(sleigh);
//
//	//Creating lights components
//	shared_ptr<Entity> directionalLight(new Entity);
//	directionalLight->addComp<Transform,glm::vec3, glm::vec3, glm::vec3>({ 0,1, -3 }, { 1, -1,  -3 }, { 1,1,1});
//	directionalLight->addComp<Light,LightType,glm::vec3, bool,float,float,float,float,float>(LightType::DIRECTIONAL,{1.0, 1.0, 1.0}, true,0.0f,0.0f,0.0f,0.0f,0.0f);
//
//    shared_ptr<Entity> pointLight(new Entity);
//    pointLight->addComp<Transform,glm::vec3, glm::vec3, glm::vec3>({ 0, 10, -10 }, { -1, -1,  -1 }, { 1,1,1});
//    pointLight->addComp<Light,LightType,glm::vec3, bool,float,float,float,float,float>(LightType::SPOT,{0.2, 1, 0.5}, true,0.2,0,0.0,0.78539816339,1.57079632679);
//
//    world.push_back(directionalLight);
    //world.push_back(pointLight);

	//Intializing systems

	intializeGameSettings();

	this->mainCamera = getEntityWithTag(world,"Camera");
	this->mainChar = getEntityWithTag(world,"Santa");
	charOrientation = 0;
    shared_ptr<RenderingSystem> RS(new RenderingSystem);
    shared_ptr<CollisionDetectionSystem> CS(new GiftCollectionSystem(this->mainChar));
    systems.push_back(RS);
    systems.push_back(CS);

}
std::shared_ptr<Entity> PlayState::getEntityWithTag(const std::vector<std::shared_ptr<Entity>> &entities,
                                                 std::string tag) {

    for(int i = 0; i<entities.size();i++){
        if(entities[i]->withTag(tag))
            return entities[i];
    }
    return NULL;
}
void PlayState ::intializeGameSettings()
{
	gameSettings.gameSensitivity = 1.0f;
	gameSettings.jumpAmount = 500;
	gameSettings.friction = 4.0f;
	gameSettings.gravity = 9.8f;
	gameSettings.groundLevel = 0;
	gameSettings.planeLevel = 10;
	gameSettings.ceilLevel = 28;
	gameSettings.rightBound = 50;
	gameSettings.leftBound = -50;
	gameSettings.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	gameSettings.cameraZoom = false;
	gameSettings.cameraRotate = false;
	gameSettings.cameraPan = false;
	gameSettings.spawnPosition = {0,10,35};
	gameSettings.characterRotation = 0.0f;

}

void PlayState::moveChar(double deltaTime)
{
	glm::vec3 position = mainChar->getComp<Transform>()->get_position()[3];
	int prevOrientation = charOrientation;
	bool fallen = false;


	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_UP)) gameSettings.velocity.z -=  ((float)deltaTime * gameSettings.gameSensitivity);
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_DOWN)) gameSettings.velocity.z += ((float)deltaTime * gameSettings.gameSensitivity);
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_RIGHT)) gameSettings.velocity.x += ((float)deltaTime * gameSettings.gameSensitivity);
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_LEFT)) gameSettings.velocity.x -= ((float)deltaTime * gameSettings.gameSensitivity);
	//Rotate Character 45 deg. left and right
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_E)) charOrientation++;
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_Q)) charOrientation--;

	//Only jump if you are on ground level
	if (!(position.y > 1.2*(gameSettings.planeLevel)))
	{
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_SPACE))gameSettings.velocity.y += ((float)deltaTime * gameSettings.gameSensitivity *gameSettings.jumpAmount);
    }
	//Update Rotation
	if (charOrientation>50)
	charOrientation =50;
	if(charOrientation < -50)
	charOrientation =-50;

    if (prevOrientation == charOrientation)
	gameSettings.characterRotation = 0;
	else if (prevOrientation < charOrientation)
	gameSettings.characterRotation = 0.05f;
	else if (charOrientation < prevOrientation)
	gameSettings.characterRotation = -0.05f;


	//Update Position
	position += gameSettings.velocity;
	//if on board don't allow falling
	if(position.x > -32.5 && position.x < 32.5 && position.z > -22.2 && position.z < 42.8 && position.y < gameSettings.planeLevel )
	{
	   position.y = gameSettings.planeLevel;
       gameSettings.velocity.y = 0;
	}
   if (position.y < gameSettings.groundLevel)
   {
       position.y = gameSettings.groundLevel;
       gameSettings.velocity.y = 0; 
	   fallen =  true;
   }
      if (position.y > gameSettings.ceilLevel)
   {
       position.y = gameSettings.ceilLevel;
       gameSettings.velocity.y = 0; 
   }

	 if (position.x > gameSettings.rightBound)
   {
       position.x = gameSettings.rightBound;
       gameSettings.velocity.x = 0; 
   }

   	 if (position.x < gameSettings.leftBound)
   {
       position.x = gameSettings.leftBound;
       gameSettings.velocity.x = 0; 
   }

    //Slow down respective axes
	//Friction in all directions except Y
    gameSettings.velocity *= glm::vec3(1,0,1) *((float) exp(-gameSettings.friction*deltaTime));
	//Deccelartion in Y direction
    gameSettings.velocity.y -= ((float)deltaTime*gameSettings.gravity);


	if (fallen)
	{
		mainChar->getComp<Transform>()->set_position(gameSettings.spawnPosition);
		std::shared_ptr<Player> playerComp = mainChar->getComp<Player>();
		playerComp->decrementLives();
	}
	else
		mainChar->getComp<Transform>()->set_position(position);

	    mainChar->getComp<Transform>()->update();

}

void PlayState::onDraw(double deltaTime) {
	for (auto systemIterator = systems.begin(); systemIterator != systems.end(); systemIterator++)
        (*systemIterator)->Run(world, deltaTime, gameSettings, skyLight);

		moveChar(deltaTime);
}

bool PlayState::checkGameOver()
{
	std::shared_ptr<Player> playerComp = mainChar->getComp<Player>();
	if (playerComp->getLives() == 0)
		return true;
	return false;
}

void PlayState::updateLives()
{
	std::shared_ptr<Player> playerComp = mainChar->getComp<Player>();
	std::vector<std::shared_ptr<Entity>> lives = getEntitiesWithTag(world,"Life");
		if (playerComp->getLives() == 3)
		{
			lives[0]->getComp<RenderState>()->isVisible = true;
			lives[1]->getComp<RenderState>()->isVisible = true;
			lives[2]->getComp<RenderState>()->isVisible = true;
		}
		else if (playerComp->getLives() == 2)
		{
			lives[0]->getComp<RenderState>()->isVisible = false;
			lives[1]->getComp<RenderState>()->isVisible = true;
			lives[2]->getComp<RenderState>()->isVisible = true;
		}
		else if (playerComp->getLives() == 1)
		{
			lives[0]->getComp<RenderState>()->isVisible = false;
			lives[1]->getComp<RenderState>()->isVisible = false;
			lives[2]->getComp<RenderState>()->isVisible = true;
		}
		else if (playerComp->getLives() == 0)
		{
			lives[0]->getComp<RenderState>()->isVisible = false;
			lives[1]->getComp<RenderState>()->isVisible = false;
			lives[2]->getComp<RenderState>()->isVisible = false;
		}
			lives[0]->getComp<RenderState>()->update();
			lives[1]->getComp<RenderState>()->update();
			lives[2]->getComp<RenderState>()->update();


}

std::vector<std::shared_ptr<Entity>> PlayState::getEntitiesWithTag(const std::vector<std::shared_ptr<Entity>> &entities,std::string tag) {
    std::vector<std::shared_ptr<Entity>> temp;
    for (unsigned int x = 0; x < entities.size(); ++x)
    {
        if (entities[x]->withTag(tag))
        {
            temp.push_back(entities[x]);
        }
    }
    return temp;
}
