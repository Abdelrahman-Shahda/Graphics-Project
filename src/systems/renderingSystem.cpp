#include  <systems/renderingSystem.hpp>

void RenderingSystem::drawNode(const std::shared_ptr<Transform> &node , const glm::mat4 &parent_transform_matrix){

    //getting current entity
	std::shared_ptr<Entity> entity = node->getEntity();

    std::shared_ptr<MeshRenderer> meshRenderer = entity->getComp<MeshRenderer>();

    glm::mat4 transform_matrix = parent_transform_matrix * node->get_transform();

	//Drawing Mesh on screen
	//Value of other parameters should be set before
	meshRenderer->renderMesh(transform_matrix);
	//Calling function on children of current entity
    std::vector<std::shared_ptr<Transform>> childern = node->get_children();
    for(int i =0;i<childern.size();i++){
        drawNode(childern[i],transform_matrix);
    }
 }

void RenderingSystem::updateCameraPosition(double delta_time)
{
    ctptr->set_position(ccptr->getPosition());
    glm::mat4 camPosition = ctptr->get_position();
    glm::vec3 position (camPosition[0][3],camPosition[1][3],camPosition[2][3]);
    cptr->setEyePosition(position);
 	ccptr->update(delta_time);
}

void RenderingSystem::Run(const std::vector<std::shared_ptr<Entity>> &entities,double delta_time){

    //Get enitities with mesh Component to render them
    std::vector<std::shared_ptr<Entity>> meshEntities = this->getEntitiesWithComponents<MeshRenderer, Transform>(entities);
    //Get camera Entities
    std::vector<std::shared_ptr<Entity>> cameraEntities = this->getEntitiesWithComponents<Camera, Transform, FlyCameraController>(entities);

    //Taking the main camera which is the first index in the array
    cptr = cameraEntities[0]->getComp<Camera>();
    ctptr = cameraEntities[0]->getComp<Transform>();
    ccptr = cameraEntities[0]->getComp<FlyCameraController>();
    //Updating Camera position and Getting view Projection
    this->updateCameraPosition(delta_time);
	glm::mat4 viewProjection = cptr->getVPMatrix();

	//Start Drawing the screen
	//clear screen to draw next frame
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Looping on entities to draw the from parent to children nodes
    for (unsigned int x = 0; x < meshEntities.size(); ++x)
	{
        std:: shared_ptr<Transform> tptr = meshEntities[x]->getComp<Transform>();
		//Call this recursive function only on parent nodes
        if(tptr->get_parent() == nullptr)
            this->drawNode(tptr,viewProjection);
    }

}
