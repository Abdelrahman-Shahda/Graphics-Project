//
// Created by Shaimaa on 11/29/2020.
//
#include <gameStates/playState.hpp>

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
	shared_ptr<Mesh> meshPtr1(new Mesh);
	shared_ptr<Mesh> meshPtr2(new Mesh);
    shared_ptr<Mesh> meshPtr3(new Mesh);
	shared_ptr<Mesh> skyMesh(new Mesh);
	MeshUtils::Cuboid(*meshPtr1, true);
	MeshUtils::Sphere(*meshPtr2);
	MeshUtils::loadOBJ(*meshPtr3,ASSETS_DIR"/models/Batman/batman.obj");
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

	shared_ptr<Resources::Texture> albedoTexture(new Texture("albedo",ASSETS_DIR"/image/material/albedo.jpg"));
    shared_ptr<Resources::Texture> specularTexture(new Texture("specular",ASSETS_DIR"/image/material/specular.jpg"));
    shared_ptr<Resources::Texture> emissiveTexture(new Texture("emissive",ASSETS_DIR"/image/material/emissive.jpg"));
	
	//Material classes
	shared_ptr<Resources::Material> material(new Material(shaderProgram));
	material->addTexture(albedoTexture, defaultSampler);
    material->addTexture(specularTexture, defaultSampler);
    material->addTexture(emissiveTexture, defaultSampler);
	material->addShaderParameter(skyLightTopColor);
	material->addShaderParameter(skyLightMiddleColor);
	material->addShaderParameter(skyLightBottomColor);
	
	shared_ptr<Resources::Material> material2(new Material(shaderProgram));
	material2->addTexture(albedoTexture, customizedSampler);
	material2->addTexture(specularTexture, customizedSampler);
	material2->addTexture(emissiveTexture, customizedSampler);
	material2->addShaderParameter(skyLightTopColor);
	material2->addShaderParameter(skyLightMiddleColor);
	material2->addShaderParameter(skyLightBottomColor);
	
	//Intializing Camera component
	shared_ptr<Entity> mainCamera(new Entity);
	std::shared_ptr<Camera> cameraPtr= mainCamera->addComp<Camera>();
	std::shared_ptr<Transform> transformPtr= mainCamera->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 10, 10, 10 }, {0, 0, 0 }, { 1,1,1 });
	mainCamera->addComp<FlyCameraController, Application*,std::shared_ptr<Camera>>(applicationPtr,cameraPtr,transformPtr);
	world.push_back(mainCamera);

	//Creating entities
	shared_ptr<Entity> entity2(new Entity);
    shared_ptr<Entity> entity3(new Entity);
	shared_ptr<Entity> entity4(new Entity);

	entity2->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr1, material2);
	entity2->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 10,10, 8 }, { 0, 0,  0 }, { 1,1,1});
    entity2->addComp<RenderState>();
	entity3->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr2, material);
	entity3->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 5, 10, 8 }, { 0, 0, 0 }, { 1, 1,  1 });
    entity3->addComp<RenderState,bool>(true);
	entity4->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr3, material);
	entity4->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 15, 10, 8 }, {0, 0, 0 }, { 1, 1, 1 });
    entity4->addComp<RenderState>();
	world.push_back(entity2);
	world.push_back(entity3);
	world.push_back(entity4);

	//Creating lights components
	shared_ptr<Entity> directionalLight(new Entity);
	directionalLight->addComp<Transform,glm::vec3, glm::vec3, glm::vec3>({ 0,1, 3 }, { 0, 1,  3 }, { 1,1,1});
	directionalLight->addComp<Light,LightType,glm::vec3, bool,float,float,float,float,float>(LightType::DIRECTIONAL,{1, 0.8, 0.2}, true,0.0f,0.0f,0.0f,0.0f,0.0f);

    shared_ptr<Entity> pointLight(new Entity);
    pointLight->addComp<Transform,glm::vec3, glm::vec3, glm::vec3>({ 3, 2, 3 }, { -1, -1,  -1 }, { 1,1,1});
    pointLight->addComp<Light,LightType,glm::vec3, bool,float,float,float,float,float>(LightType::SPOT,{0.2, 1, 0.5}, true,0.2,0,0.0,0.78539816339,1.57079632679);

    world.push_back(directionalLight);
    world.push_back(pointLight);
}

void PlayState::onDraw(double deltaTime) {
	for (auto systemIterator = systems.begin(); systemIterator != systems.end(); systemIterator++)
		(*systemIterator)->Run(world, deltaTime, skyLight);
}