#include  <systems/renderingSystem.hpp>

void RenderingSystem::Run(const std::vector<std::shared_ptr<Entity>> entities){


    //Get enitities with mesh Component to render them
    std::vector<std::shared_ptr<Entity>> meshEntities = this->getEntitiesByComponents<MeshRenderer, Transform>(entities);

    //Get camera Entities
    std::vector<std::shared_ptr<Entity>> cameraEntities = this->getEntitiesByComponents<Camera, Transform, FlyCameraController>(entities);

    //Taking the main camera which is the first index in the array
    cptr = cameraEntities[0]->getComp<Camera>();
    ctptr = cameraEntities[0]->getComp<Transform>();
    ccptr = cameraEntities[0]->getComp<FlyCameraController>();

    //Adjusting camera component
    cptr->setVerticalFieldOfView(ccptr->getVerticalFieldOfView());
    ctptr->set_position(ccptr->getPosition());
    ctptr->set_rotation({ccptr->getYaw(), ccptr->getPitch(),0});

    //Getting View Matrix
    glm::vec4 direction=glm::vec4({0,0,-1,0})*ctptr->get_transform();
    glm::vec4 up=glm::vec4({0,1,0,0})*ctptr->get_transform();
    glm:: mat4 camPosition=ctptr->get_position();
    glm::vec3 position(camPosition[0][3],camPosition[1][3],camPosition[2][3]);
    glm::mat4 viewProjection=cptr->getVPMatrix(position,(glm::vec3)(direction),(glm::vec3)(up));

    //Looping on entities
    for(auto iterator=meshEntities)




    //clear screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
