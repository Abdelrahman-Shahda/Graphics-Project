#include  <systems/renderingSystem.hpp>
#include <entity.hpp>

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

glm::mat4 RenderingSystem::getCameraViewProjectionMatrix()
{
	//Adjusting camera component
	//cptr->setVerticalFieldOfView(ccptr->getVerticalFieldOfView());
	//ctptr->set_rotation({ ccptr->getYaw(), ccptr->getPitch(),0 });
	//ctptr->set_position(ccptr->getPosition());
	//Getting View Projection Matrix of Main Camera
	//glm::vec4 direction = glm::vec4({ 0,0,-1,1 })*ctptr->get_transform();
	//glm::vec4 up = glm::vec4({ 0,1,0,1 })*ctptr->get_transform();
	//glm::mat4 camPosition = ctptr->get_position();
	//glm::vec3 position((camPosition[0][3]/camPosition[3][3]), (camPosition[1][3]/camPosition[3][3]), (camPosition[2][3]/camPosition[3][3]));

	return cptr->getVPMatrix();
    //return glm::mat4(glm::vec4(0.397748,-0.408248,-0.578506,-0.577350),glm::vec4(0,0.816497,-0.578506,-0.577350),glm::vec4(-0.397748,-0.408248,0.578506,-0.577350),glm::vec4(0,0,17.154982,17.320507));
}

void RenderingSystem::updateCameraPosition(double delta_time)
{
    ctptr->set_position(ccptr->getPosition());
    glm::mat4 camPosition = ctptr->get_position();
    glm::vec3 position (camPosition[0][3],camPosition[1][3],camPosition[2][3]);
    cptr->setEyePosition(position);
 	//glm::vec4 direction = glm::vec4({ 0,0,-1,1 })*ctptr->get_transform();
	//glm::vec4 up = glm::vec4({ 0,1,0,1 })*ctptr->get_transform();
    //glm::vec4 up = glm::vec4({ 0,1,0,1 });

	//glm::vec3 position((camPosition[0][3]/camPosition[3][3]), (camPosition[1][3]/camPosition[3][3]), (camPosition[2][3]/camPosition[3][3]));
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
      //Updating Camera position
    this->updateCameraPosition(delta_time);
    	//Getting view projection matrix of camera
	glm::mat4 viewProjection =this->getCameraViewProjectionMatrix();



	//Start Drawing the screen
	//clear screen
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //Looping on entities to draw the from parent to children nodes
    for (unsigned int x = 0; x < meshEntities.size(); ++x)
	{
        std:: shared_ptr<Transform> tptr = meshEntities[x]->getComp<Transform>();

		//Call this recursive function only on parent nodes
        if(tptr->get_parent() == nullptr){

            this->drawNode(tptr,viewProjection);
        }

    }

}
