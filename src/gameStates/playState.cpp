//
// Created by Shaimaa on 11/29/2020.
//
#include <gameStates/playState.hpp>
#include <glm/gtx/string_cast.hpp>
#include <time.h>
#include <random>
void PlayState::onEnter() {

	//Intializing resources
	//shaders
	shared_ptr< Resources::ShaderProgram> shaderProgram(new Resources::ShaderProgram);
	SceneLoader * sceneLoader = new SceneLoader(ASSETS_DIR"/scenes/scene.json");



	world = sceneLoader->loadEntities(applicationPtr);
	skyLight = sceneLoader->loadSky();
	//Light shaders
	shaderProgram->create();
	shaderProgram->attach(ASSETS_DIR"/shaders/light_transform.vert", GL_VERTEX_SHADER);
	shaderProgram->attach(ASSETS_DIR "/shaders/light_array.frag", GL_FRAGMENT_SHADER);
	shaderProgram->link();
    shared_ptr<Resources::Sampler> customizedSampler(new Sampler(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_NEAREST));

    //snow
    shared_ptr<Mesh> snowMesh(new Mesh);
    MeshUtils::Sphere(*snowMesh,glm::vec2{32,16},false);
    shared_ptr<Resources::Texture> snowTexture(new Texture("albedo",ASSETS_DIR"/image/material/snow.jpg"));
    shared_ptr<Resources::Material> snowMaterial(new Material(shaderProgram));
    snowMaterial->addTexture(snowTexture,customizedSampler);
    for (int i=30;i>0;i=i-10)
        for (int j=-50;j<50;j=j+10)
            for (int k=-15;k<45;k=k+10)
            {
                shared_ptr<Entity> snow(new Entity("Snow"));
                snow->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(snowMesh, snowMaterial);
                snow->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ j, i, k }, { 0, 0, 0 }, { 0.5, 0.5,  0.5 });
                snow->getComp<Transform>()->update();
                snow->addComp<RenderState,bool>(true);
                snow->getComp<RenderState>()->enable_blending = true;
                snow->getComp<RenderState>()->update();
                world.push_back(snow);
            }

    this->mainCamera = getEntityWithTag(world,"Camera");
    this->mainChar = getEntityWithTag(world,"Santa");

    shared_ptr<Transform> mainTransformPtr = mainChar->getComp<Transform>();
    //Scores
    shared_ptr<Mesh> scoreMesh_0(new Mesh);
    shared_ptr<Mesh> scoreMesh_1(new Mesh);
    shared_ptr<Mesh> scoreMesh_2(new Mesh);
    shared_ptr<Mesh> scoreMesh_3(new Mesh);
    shared_ptr<Mesh> scoreMesh_4(new Mesh);
    shared_ptr<Mesh> scoreMesh_5(new Mesh);
    shared_ptr<Mesh> scoreMesh_6(new Mesh);
    shared_ptr<Mesh> scoreMesh_7(new Mesh);
    shared_ptr<Mesh> scoreMesh_8(new Mesh);
    shared_ptr<Mesh> scoreMesh_9(new Mesh);

    MeshUtils::loadOBJ(*scoreMesh_0,ASSETS_DIR"/models/Numbers/0.obj");
    MeshUtils::loadOBJ(*scoreMesh_1,ASSETS_DIR"/models/Numbers/1.obj");
    MeshUtils::loadOBJ(*scoreMesh_2,ASSETS_DIR"/models/Numbers/2.obj");
    MeshUtils::loadOBJ(*scoreMesh_3,ASSETS_DIR"/models/Numbers/3.obj");
    MeshUtils::loadOBJ(*scoreMesh_4,ASSETS_DIR"/models/Numbers/4.obj");
    MeshUtils::loadOBJ(*scoreMesh_5,ASSETS_DIR"/models/Numbers/5.obj");
    MeshUtils::loadOBJ(*scoreMesh_6,ASSETS_DIR"/models/Numbers/6.obj");
    MeshUtils::loadOBJ(*scoreMesh_7,ASSETS_DIR"/models/Numbers/7.obj");
    MeshUtils::loadOBJ(*scoreMesh_8,ASSETS_DIR"/models/Numbers/8.obj");
    MeshUtils::loadOBJ(*scoreMesh_9,ASSETS_DIR"/models/Numbers/9.obj");

    shared_ptr<Resources::Texture> scoreTexture(new Texture("albedo",ASSETS_DIR"/image/material/heart.jpg"));
    shared_ptr<Resources::Material> scoreMaterial(new Material(shaderProgram));

    scoreMaterial->addTexture(scoreTexture, customizedSampler);
    //score
    shared_ptr<Entity> score_0(new Entity("Score"));
    score_0->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(scoreMesh_0, scoreMaterial);
    score_0->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ -40, 50, 50 }, { 3*3.14/2, 3.14, 0 }, { 0.5, 0.5,  0.5 });
    score_0->getComp<Transform>()->update();
    score_0->addComp<RenderState,bool>(true);
    world.push_back(score_0);

    shared_ptr<Entity> score_1(new Entity("Score"));
    score_1->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(scoreMesh_1, scoreMaterial);
    score_1->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ -40, 50, 50 }, { 3*3.14/2, 3.14, 0 }, { 0.5, 0.5,  0.5 });
    score_1->getComp<Transform>()->update();
    score_1->addComp<RenderState,bool>(true);
    world.push_back(score_1);

    shared_ptr<Entity> score_2(new Entity("Score"));
    score_2->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(scoreMesh_2, scoreMaterial);
    score_2->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ -40, 50, 50 }, { 3*3.14/2, 3.14, 0 }, { 0.5, 0.5,  0.5 });
    score_2->getComp<Transform>()->update();
    score_2->addComp<RenderState,bool>(true);
    world.push_back(score_2);

    shared_ptr<Entity> score_3(new Entity("Score"));
    score_3->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(scoreMesh_3, scoreMaterial);
    score_3->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ -40, 50, 50 }, { 3*3.14/2, 3.14, 0 }, { 0.5, 0.5,  0.5 });
    score_3->getComp<Transform>()->update();
    score_3->addComp<RenderState,bool>(true);
    world.push_back(score_3);

    shared_ptr<Entity> score_4(new Entity("Score"));
    score_4->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(scoreMesh_4, scoreMaterial);
    score_4->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ -40, 50, 50 }, { 3*3.14/2, 3.14, 0 }, { 0.5, 0.5,  0.5 });
    score_4->getComp<Transform>()->update();
    score_4->addComp<RenderState,bool>(true);
    world.push_back(score_4);

    shared_ptr<Entity> score_5(new Entity("Score"));
    score_5->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(scoreMesh_5, scoreMaterial);
    score_5->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ -40, 50, 50 }, { 3*3.14/2, 3.14, 0 }, { 0.5, 0.5,  0.5 });
    score_5->getComp<Transform>()->update();
    score_5->addComp<RenderState,bool>(true);
    world.push_back(score_5);

    shared_ptr<Entity> score_6(new Entity("Score"));
    score_6->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(scoreMesh_6, scoreMaterial);
    score_6->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ -40, 50, 50 }, { 3*3.14/2, 3.14, 0 }, { 0.5, 0.5,  0.5 });
    score_6->getComp<Transform>()->update();
    score_6->addComp<RenderState,bool>(true);
    world.push_back(score_6);

    shared_ptr<Entity> score_7(new Entity("Score"));
    score_7->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(scoreMesh_7, scoreMaterial);
    score_7->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ -40, 50, 50 }, { 3*3.14/2, 3.14, 0 }, { 0.5, 0.5,  0.5 });
    score_7->getComp<Transform>()->update();
    score_7->addComp<RenderState,bool>(true);
    world.push_back(score_7);

    shared_ptr<Entity> score_8(new Entity("Score"));
    score_8->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(scoreMesh_8, scoreMaterial);
    score_8->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ -40, 50, 50 }, { 3*3.14/2, 3.14, 0 }, { 0.5, 0.5,  0.5 });
    score_8->getComp<Transform>()->update();
    score_8->addComp<RenderState,bool>(true);
    world.push_back(score_8);

    shared_ptr<Entity> score_9(new Entity("Score"));
    score_9->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(scoreMesh_9, scoreMaterial);
    score_9->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ -40, 50, 50 }, { 3*3.14/2, 3.14, 0 }, { 0.5, 0.5,  0.5 });
    score_9->getComp<Transform>()->update();
    score_9->addComp<RenderState,bool>(true);
    world.push_back(score_9);

    //Make score follow Main character
    score_0->getComp<Transform>()->set_parent(mainTransformPtr);
    mainTransformPtr->add_child( score_0->getComp<Transform>());
    score_1->getComp<Transform>()->set_parent(mainTransformPtr);
    mainTransformPtr->add_child( score_1->getComp<Transform>());
    score_2->getComp<Transform>()->set_parent(mainTransformPtr);
    mainTransformPtr->add_child( score_2->getComp<Transform>());
    score_3->getComp<Transform>()->set_parent(mainTransformPtr);
    mainTransformPtr->add_child( score_3->getComp<Transform>());
    score_4->getComp<Transform>()->set_parent(mainTransformPtr);
    mainTransformPtr->add_child( score_4->getComp<Transform>());
    score_5->getComp<Transform>()->set_parent(mainTransformPtr);
    mainTransformPtr->add_child( score_5->getComp<Transform>());
    score_6->getComp<Transform>()->set_parent(mainTransformPtr);
    mainTransformPtr->add_child( score_6->getComp<Transform>());
    score_7->getComp<Transform>()->set_parent(mainTransformPtr);
    mainTransformPtr->add_child( score_7->getComp<Transform>());
    score_8->getComp<Transform>()->set_parent(mainTransformPtr);
    mainTransformPtr->add_child( score_8->getComp<Transform>());
    score_9->getComp<Transform>()->set_parent(mainTransformPtr);
    mainTransformPtr->add_child( score_9->getComp<Transform>());

	//Intializing systems
	intializeGameSettings();

	charOrientation = 0;
    shared_ptr<RenderingSystem> RS(new RenderingSystem);
    shared_ptr<CollisionDetectionSystem> CS(new GiftCollectionSystem(this->mainChar));
    shared_ptr<CollisionDetectionSystem> ES(new elfCollisionSystem(mainChar));
    systems.push_back(RS);
    systems.push_back(CS);
    systems.push_back(ES);
    this->elf_entity=elf_entity;
}
std::shared_ptr<Entity> PlayState::getEntityWithTag(const std::vector<std::shared_ptr<Entity>> &entities,
                                                 std::string tag) {

    for(int i = 0; i<entities.size();i++){
        if(entities[i]->withTag(tag))
            return entities[i];
    }
    return NULL;
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

    //Only jump if you are on g level
    if(applicationPtr->getKeyboard().isPressed(GLFW_KEY_SPACE))gameSettings.velocity.y += ((float)deltaTime * gameSettings.gameSensitivity *gameSettings.jumpAmount);
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
        updateLives();
    }
    else
        mainChar->getComp<Transform>()->set_position(position);

    mainChar->getComp<Transform>()->update();

}

void PlayState::onDraw(double deltaTime) {
    for (auto systemIterator = systems.begin(); systemIterator != systems.end(); systemIterator++)
        (*systemIterator)->Run(world, deltaTime, gameSettings, skyLight);

    moveChar(deltaTime);
    moveSnow(deltaTime);
    updateScore();
}

bool PlayState::checkGameOver()
{
    std::shared_ptr<Player> playerComp = mainChar->getComp<Player>();
    if (playerComp->getLives() == 0)
        return true;
    return false;
}

void PlayState::updateScore()
{
    std::shared_ptr<Player> playerComp = mainChar->getComp<Player>();
    std::vector<std::shared_ptr<Entity>> scores = getEntitiesWithTag(world,"Score");
    for (int i=0;i<scores.size();i++)
        if (i==playerComp->getScore())
            scores[i]->getComp<RenderState>()->isVisible = true;
        else
            scores[i]->getComp<RenderState>()->isVisible = false;
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

void PlayState::moveSnow(double deltaTime)
{
    glm::vec3 position;
    std::vector<std::shared_ptr<Entity>> snow = getEntitiesWithTag(world,"Snow");
    for (int i=0;i<snow.size();i++)
    {
        position = snow[i]->getComp<Transform>()->get_position()[3];
        position.y -= ((float)deltaTime*gameSettings.gravity);
        if (position.y < gameSettings.groundLevel)
            position.y = gameSettings.ceilLevel;

        snow[i]->getComp<Transform>()->set_position(position);
        snow[i]->getComp<Transform>()->update();

    }
}