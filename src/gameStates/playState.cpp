//
// Created by Shaimaa on 11/29/2020.
//
#include <gameStates/playState.hpp>
#include <glm/gtx/string_cast.hpp>

void PlayState::onEnter() {
	shared_ptr<RenderingSystem> RS(new RenderingSystem);
	shared_ptr<CollisionDetectionSystem> CS(new CollisionDetectionSystem);
	systems.push_back(RS);
	systems.push_back(CS);

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
	shared_ptr<Mesh> meshPtr(new Mesh);
	shared_ptr<Mesh> meshPtr2(new Mesh);
	shared_ptr<Mesh> skyMesh(new Mesh);
	shared_ptr<Mesh> iceMesh(new Mesh);
	glm::vec3 min;
    glm::vec3 max;

	MeshUtils::loadOBJ(*meshPtr,ASSETS_DIR"/models/Santa Claus/santa.obj");
	MeshUtils::Cuboid(*meshPtr2,true);
    MeshUtils::Plane(*iceMesh,{1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});
	std::cout <<"Min: x " <<meshPtr->getMinPoint().x << " y "<< meshPtr->getMinPoint().y << " z "<< meshPtr->getMinPoint().z <<std::endl;
    std::cout <<"Max: x " <<meshPtr->getMaxPoint().x << " y "<< meshPtr->getMaxPoint().y << " z "<< meshPtr->getMaxPoint().z <<std::endl;


	MeshUtils::Cuboid(*skyMesh);

	//Sky entity
	shared_ptr<Entity> skyTest(new Entity);
	shared_ptr<Resources::Material> skyMaterial(new Material(skyProgram));
	skyTest->addComp<SkyLight, bool, glm::vec3, glm::vec3, glm::vec3>(true, { 0.1, 0.1, 0.1 }, { 0.35, 0.35, 0.4 }, { 0.25, 0.25, 0.25 });
	skyTest->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(skyMesh, skyMaterial);
	skyTest->addComp<RenderState>();
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
    shared_ptr<Resources::Sampler> iceSampler(new Sampler(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_NEAREST));
	shared_ptr<Resources::Texture> santaTexture(new Texture("albedo",ASSETS_DIR"/image/material/santa.jpg"));
	shared_ptr<Resources::Texture> specularTexture(new Texture("specular",ASSETS_DIR"/image/material/santa_spec.jpg"));
    shared_ptr<Resources::Texture> emissiveTexture(new Texture("emissive",ASSETS_DIR"/image/material/santa.jpg"));
    shared_ptr<Resources::Texture> iceTexture(new Texture("albedo",ASSETS_DIR"/image/material/ice.jpg"));

    //Material classes
	shared_ptr<Resources::Material> material(new Material(shaderProgram));
    shared_ptr<Resources::Material> material2(new Material(shaderProgram));
	material->addTexture(santaTexture, customizedSampler);
	material->addTexture(specularTexture,customizedSampler);
	//material2->addTexture(emissiveTexture, customizedSampler);
	material->addShaderParameter(skyLightTopColor);
	material->addShaderParameter(skyLightMiddleColor);
	material->addShaderParameter(skyLightBottomColor);
    material2->addTexture(iceTexture,iceSampler);
    material2->addShaderParameter(skyLightTopColor);
    material2->addShaderParameter(skyLightMiddleColor);
    material2->addShaderParameter(skyLightBottomColor);

	//Intializing Camera component
	shared_ptr<Entity> mainCamera(new Entity);
	std::shared_ptr<Camera> cameraPtr= mainCamera->addComp<Camera>();
	std::shared_ptr<Transform> camTransformPtr= mainCamera->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 10, 10, -10 }, {0, 0, 1 }, { 1,1,1 });
	camTransformPtr->update();

	mainCamera->addComp<FlyCameraController, Application*,std::shared_ptr<Camera>>(applicationPtr,cameraPtr,camTransformPtr);
	world.push_back(mainCamera);



	//Creating entities
	shared_ptr<Entity> mainChar(new Entity("Santa"));
	shared_ptr<Entity> entity3(new Entity("Gift"));
	mainChar->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr, material);
	std::shared_ptr<Transform> mainTransformPtr= mainChar->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 10, 7, 7.5 }, {0, 3.14, 0 }, { 0.5, 0.5, 0.5 });
	mainTransformPtr->update();
    mainChar->addComp<RenderState>();
	world.push_back(mainChar);

	entity3->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr2, material);
	entity3->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 10, 8, -13 }, { 0, 0, 0 }, { 1, 1,  1 });
	entity3->getComp<Transform>()->update();
    entity3->addComp<RenderState,bool>(true);
	world.push_back(entity3);

	//icePlane
    shared_ptr<Entity> icePlane(new Entity());
    icePlane->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(iceMesh, material2);
    std::shared_ptr<Transform> icePtr= icePlane->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 10, 7, 7.5 }, {0, 0, 0 }, { 60, 1, 60 });
    icePtr->update();
    icePlane->addComp<RenderState,bool>(true);
    world.push_back(icePlane);
    //Make camera follow Main character
    camTransformPtr->set_parent(mainTransformPtr);
    mainTransformPtr->add_child(camTransformPtr);

	//Creating lights components
	shared_ptr<Entity> directionalLight(new Entity);
	directionalLight->addComp<Transform,glm::vec3, glm::vec3, glm::vec3>({ 0,1, -3 }, { 1, -1,  -3 }, { 1,1,1});
	directionalLight->addComp<Light,LightType,glm::vec3, bool,float,float,float,float,float>(LightType::DIRECTIONAL,{1.0, 1.0, 1.0}, true,0.1f,0.0f,0.0f,0.0f,0.0f);

    shared_ptr<Entity> pointLight(new Entity);
    pointLight->addComp<Transform,glm::vec3, glm::vec3, glm::vec3>({ 10, 8, -10 }, { -1, -1,  -1 }, { 1,1,1});
    pointLight->addComp<Light,LightType,glm::vec3, bool,float,float,float,float,float>(LightType::SPOT,{0.2, 1, 0.5}, true,0.2,0,0.0,0.78539816339,1.57079632679);

    world.push_back(directionalLight);
    //world.push_back(pointLight);

	gameSettings.gameSensitivity = 0.1f;
	gameSettings.jumpAmount = 500;
	gameSettings.friction = 4.0f;
	gameSettings.gravity = 9.8f;
	gameSettings.groundLevel = 8;
	gameSettings.ceilLevel = 28;
	gameSettings.rightBound =60 ;
	gameSettings.leftBound = -40;
	gameSettings.velocity = glm::vec3(0.0f,0.0f,0.0f);
	gameSettings.cameraZoom = false;
	gameSettings.cameraRotate = false;
	gameSettings.cameraPan = false;
	this->mainCamera = mainCamera;
	this->mainChar = mainChar;
	gameSettings.characterRotation = 0.0f;
	charOrientation = 0;

}
void PlayState::moveChar(double deltaTime)
{
	glm::vec3 position = mainChar->getComp<Transform>()->get_position()[3];
	int prevOrientation = charOrientation;

	//Only move if you are on ground level
	if (!(position.y > 1.2*gameSettings.groundLevel))
	{
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_UP)) gameSettings.velocity.z -=  ((float)deltaTime * gameSettings.gameSensitivity);
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_DOWN)) gameSettings.velocity.z += ((float)deltaTime * gameSettings.gameSensitivity);
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_RIGHT)) gameSettings.velocity.x += ((float)deltaTime * gameSettings.gameSensitivity);
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_LEFT)) gameSettings.velocity.x -= ((float)deltaTime * gameSettings.gameSensitivity);
	//Rotate Character 45 deg. left and right
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_E)) charOrientation++;
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_Q)) charOrientation--;
	}
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_SPACE))gameSettings.velocity.y += ((float)deltaTime * gameSettings.gameSensitivity *gameSettings.jumpAmount);

	//Update Rotation
	if (charOrientation>2000)
	charOrientation =2000;
	if(charOrientation < -2000)
	charOrientation =-2000;

    if (prevOrientation == charOrientation)
	gameSettings.characterRotation = 0;
	else if (prevOrientation < charOrientation)
	gameSettings.characterRotation = 0.001f;
	else if (charOrientation < prevOrientation)
	gameSettings.characterRotation = -0.001f;


	//Update Position
	position += gameSettings.velocity;
   if (position.y < gameSettings.groundLevel)
   {
       position.y = gameSettings.groundLevel;
       gameSettings.velocity.y = 0; 
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


	mainChar->getComp<Transform>()->set_position(position);
	mainChar->getComp<Transform>()->update();
}

void PlayState::onDraw(double deltaTime) {
	for (auto systemIterator = systems.begin(); systemIterator != systems.end(); systemIterator++)
	{
        moveChar(deltaTime);
		(*systemIterator)->Run(world, deltaTime,gameSettings,skyLight);

	}
}