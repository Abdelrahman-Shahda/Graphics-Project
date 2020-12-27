//
// Created by Shaimaa on 11/29/2020.
//
#include <gameStates/playState.hpp>

void PlayState::onEnter() {
	shared_ptr<RenderingSystem> RS(new RenderingSystem);
	systems.push_back(RS);

	//Intializing resources
	shared_ptr< Resources::ShaderProgram> shaderProgram(new Resources::ShaderProgram);
	shared_ptr<Resources::Vector4ShaderParamter> tint(new Resources::Vector4ShaderParamter("tint", glm::vec4(1, 1, 1, 1)));
	shaderProgram->create();
	shaderProgram->attach(ASSETS_DIR"/shaders/transform.vert", GL_VERTEX_SHADER);
	shaderProgram->attach(ASSETS_DIR "/shaders/tint.frag", GL_FRAGMENT_SHADER);
	//shaderProgram->attach(ASSETS_DIR"/shaders/multiple_attributes.vert", GL_VERTEX_SHADER);
    //shaderProgram->attach(ASSETS_DIR"/shaders/varying_color.frag", GL_FRAGMENT_SHADER);
	shaderProgram->link();
	shared_ptr<Mesh> meshPtr1(new Mesh);
	shared_ptr<Mesh> meshPtr2(new Mesh);
    shared_ptr<Mesh> meshPtr3(new Mesh);

	MeshUtils::Cuboid(*meshPtr1, true);
	MeshUtils::Sphere(*meshPtr2);
	MeshUtils::loadOBJ(*meshPtr3,ASSETS_DIR"/models/Batman/batman.obj");

	shared_ptr<Resources::Material> material(new Material(shaderProgram));
	material->addShaderParameter(tint);

	//Intializing Camera component
	shared_ptr<Entity> mainCamera(new Entity);
	std::shared_ptr<Camera> cameraPtr= mainCamera->addComp<Camera>();
	std::shared_ptr<Transform> transformPtr= mainCamera->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 10, 10, 10 }, {0, 0, 0 }, { 1,1,1 });
	mainCamera->addComp<FlyCameraController, Application*,std::shared_ptr<Camera>>(applicationPtr,cameraPtr,transformPtr);
	world.push_back(mainCamera);

	//Two entities
	shared_ptr<Entity> entity2(new Entity);
    shared_ptr<Entity> entity3(new Entity);
	shared_ptr<Entity> entity4(new Entity);

	entity2->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr1, material);
	entity2->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ -2,1, -2 }, { 0, 0,  0 }, { 1,1,1});

	entity3->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr2, material);
	entity3->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 0, -1, 0 }, { 0, 0, 0 }, { 1, 1,  1 });

	entity4->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr3, material);
	entity4->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 3, 2, 4 }, { -3.14/2, 0, 0 }, { 1, 1, 1 });
	world.push_back(entity2);
	world.push_back(entity3);
	world.push_back(entity4);


	//OpenGL Rendering Settings
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

}

void PlayState::onDraw(double deltaTime) {
	for (auto systemIterator = systems.begin(); systemIterator != systems.end(); systemIterator++)
		(*systemIterator)->Run(world, deltaTime);
}