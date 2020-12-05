//
// Created by Shaimaa on 11/29/2020.
//

#include <game_states/play_state.hpp>

void play_state::onEnter() {
	//Intializing resources
	shared_ptr< Resources::ShaderProgram> shaderProgram(new Resources::ShaderProgram);
	//Be r3ayet Shahod el HACKER
	shared_ptr<Resources::Vector4ShaderParamter> tint(new Resources::Vector4ShaderParamter("tint", glm::vec4(1, 1, 1, 1)));
	shaderProgram->create();
	shaderProgram->attach(ASSETS_DIR"/shaders/transform.vert", GL_VERTEX_SHADER);
	shaderProgram->attach(ASSETS_DIR "/shaders/tint.frag", GL_FRAGMENT_SHADER);
	shaderProgram->link();
	shared_ptr<Mesh> meshPtr1(new Mesh);
	shared_ptr<Mesh> meshPtr2(new Mesh);
	MeshUtils::Cuboid(*meshPtr1, true);
	MeshUtils::Sphere(*meshPtr2);

	shared_ptr<Resources::Material> material(new Material(shaderProgram));
	material->addShaderParameter(tint);

	//TODO:: set paramaters in material

	//Intializing Camera component
	shared_ptr<Entity> mainCamera(new Entity);
	mainCamera->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 0, -1, 0 }, { glm::pi<float>() / 4, glm::pi<float>() / 4, 0 }, { 7, 2,  7 });
	mainCamera->addComp<Camera>();
	mainCamera->addComp<FlyCameraController, Application*>(applicationPtr);
	world.push_back(mainCamera);

	//Two entities
	shared_ptr<Entity> entity2(new Entity);
	shared_ptr<Entity> entity3(new Entity);
	entity2->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr1, material);
	entity2->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 0, -1, 0 }, { 0, 0,  0 }, { 7, 2,  7 });

	entity3->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr2, material);
	entity3->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ 0, -1, 0 }, { 0, 0,  0 }, { 7, 2,  7 });
	world.push_back(entity2);
	world.push_back(entity3);


	//openGL rendering settings
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

}

void play_state::onDraw1() {
	renderingSystem.Run(world,10.0f);
}