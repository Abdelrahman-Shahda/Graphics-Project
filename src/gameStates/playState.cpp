//
// Created by Shaimaa on 11/29/2020.
//
#include <gameStates/playState.hpp>
#include <glm/gtx/string_cast.hpp>

void PlayState::onEnter() {
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
	shared_ptr<Mesh> meshPtr(new Mesh);
	shared_ptr<Mesh> meshPtr2(new Mesh);
	shared_ptr<Mesh> skyMesh(new Mesh);
	glm::vec3 min;
    glm::vec3 max;

	MeshUtils::loadOBJ(*meshPtr,ASSETS_DIR"/models/Santa Claus/santa.obj");
	MeshUtils::Sphere(*meshPtr2);

	std::cout <<"Min: x " <<min.x << " y "<< min.y << " z "<< min.z <<std::endl;
    std::cout <<"Max: x " <<max.x << " y "<< max.y << " z "<< max.z <<std::endl;


	MeshUtils::Cuboid(*skyMesh);

	//Sky entity
	shared_ptr<Entity> skyTest(new Entity);
	shared_ptr<Resources::Material> skyMaterial(new Material(skyProgram));
	skyTest->addComp<SkyLight, bool, glm::vec3, glm::vec3, glm::vec3>(true, { 0.25, 0.3, 0.5 }, { 0.35, 0.35, 0.4 }, { 0.25, 0.25, 0.25 });
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

	shared_ptr<Resources::Texture> santaTexture(new Texture("emissive",ASSETS_DIR"/image/material/santa.jpg"));
	shared_ptr<Resources::Texture> specularTexture(new Texture("emissive",ASSETS_DIR"/image/material/santa_spec.jpg"));
	
	//Material classes
	shared_ptr<Resources::Material> material(new Material(shaderProgram));
	material->addTexture(santaTexture, customizedSampler);
	material->addShaderParameter(skyLightTopColor);
	material->addShaderParameter(skyLightMiddleColor);
	material->addShaderParameter(skyLightBottomColor);
	
	//Intializing Camera component
	shared_ptr<Entity> mainCamera(new Entity);
	std::shared_ptr<Camera> cameraPtr= mainCamera->addComp<Camera>();
	std::shared_ptr<Transform> camTransformPtr= mainCamera->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 0, 10, -10 }, {0, 0, 1 }, { 1,1,1 });
	camTransformPtr->update();

	mainCamera->addComp<FlyCameraController, Application*,std::shared_ptr<Camera>>(applicationPtr,cameraPtr,camTransformPtr);
	world.push_back(mainCamera);



	//Creating entities
	shared_ptr<Entity> mainChar(new Entity);
	shared_ptr<Entity> entity3(new Entity);
	mainChar->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr, material);
	std::shared_ptr<Transform> mainTransformPtr= mainChar->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 10, 8, 7.5 }, {0, 3.14, 0 }, { 0.5, 0.5, 0.5 });
	mainTransformPtr->update();
    mainChar->addComp<RenderState>();
	world.push_back(mainChar);

	entity3->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr2, material);
	entity3->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 10, 8, -13 }, { 0, 0, 0 }, { 1, 1,  1 });
	entity3->getComp<Transform>()->update();
    entity3->addComp<RenderState,bool>(true);
	world.push_back(entity3);
	//Make camera follow Main character
     camTransformPtr->set_parent(mainTransformPtr);
	 mainTransformPtr->add_child(camTransformPtr);

	//Creating lights components
	shared_ptr<Entity> directionalLight(new Entity);
	directionalLight->addComp<Transform,glm::vec3, glm::vec3, glm::vec3>({ 0,1, 3 }, { 0, 1,  3 }, { 1,1,1});
	directionalLight->addComp<Light,LightType,glm::vec3, bool,float,float,float,float,float>(LightType::DIRECTIONAL,{1, 0.8, 0.2}, true,0.0f,0.0f,0.0f,0.0f,0.0f);

    shared_ptr<Entity> pointLight(new Entity);
    pointLight->addComp<Transform,glm::vec3, glm::vec3, glm::vec3>({ 3, 2, 3 }, { -1, -1,  -1 }, { 1,1,1});
    pointLight->addComp<Light,LightType,glm::vec3, bool,float,float,float,float,float>(LightType::SPOT,{0.2, 1, 0.5}, true,0.2,0,0.0,0.78539816339,1.57079632679);

    world.push_back(directionalLight);
    world.push_back(pointLight);

	gameSensitivity = 1.0f;
	friction = 2.0f;
	gravity = 9.8f;
	groundLevel = 8;
	velocity = glm::vec3(0.0f,0.0f,0.0f);
	this->mainCamera = mainCamera;
	this->mainChar = mainChar;
}
void PlayState::moveChar(double deltaTime)
{
	glm::vec3 position = mainChar->getComp<Transform>()->get_position()[3];
	glm::vec3 direction = mainCamera->getComp<Camera>()->getDirection();
	glm::vec3 up = mainCamera->getComp<Camera>()->getOriginalUp();
	glm::vec3 normal = glm::cross(direction,up);
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_UP)) velocity += direction* ((float)deltaTime * gameSensitivity);
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_DOWN)) velocity -= direction* ((float)deltaTime * gameSensitivity);
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_RIGHT)) velocity += normal*((float)deltaTime * gameSensitivity);
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_LEFT)) velocity -= normal* ((float)deltaTime * gameSensitivity);
	if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_SPACE)) velocity += up*  ((float)deltaTime * gameSensitivity);

	//Update Position
	position += velocity;
   if (position.y < groundLevel)
   {
       position.y = groundLevel;
       velocity.y = 0; 
   }
    //Slow down respective axes
    velocity *= exp(-friction*deltaTime);
    velocity.y -= gravity*deltaTime;


	mainChar->getComp<Transform>()->set_position(position);
	mainChar->getComp<Transform>()->update();
}

void PlayState::onDraw(double deltaTime) {
	for (auto systemIterator = systems.begin(); systemIterator != systems.end(); systemIterator++)
	{
		(*systemIterator)->Run(world, deltaTime, skyLight);
		moveChar(deltaTime);
	}
}