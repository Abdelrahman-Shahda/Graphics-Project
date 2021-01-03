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
void RenderingSystem::calculateDistance(std::vector<RenderObjects> &objects, const std::shared_ptr<Transform> &node,
                                        const glm::mat4 &parent_transform_matrix,const glm::mat4& cameraVPMatrix) {

    //getting current entity
    std::shared_ptr<Entity> entity = node->getEntity();

    std::shared_ptr<MeshRenderer> meshRenderer = entity->getComp<MeshRenderer>();

    glm::mat4 transform_matrix = parent_transform_matrix * node->get_transform();
    glm::vec4 transformed_origin = cameraVPMatrix* transform_matrix * glm::vec4(0, 0, 0, 1);
    float depth = transformed_origin.z / transformed_origin.w;
    objects.push_back({
        meshRenderer,
        depth,
        transform_matrix,
    });
    //Calling function on children of current entity
    std::vector<std::shared_ptr<Transform>> childern = node->get_children();
    for(int i =0;i<childern.size();i++){
        calculateDistance(objects,childern[i],transform_matrix,cameraVPMatrix);
    }
}

void RenderingSystem::updateCameraPosition(double delta_time)
{
    cptr->setEyePosition(glm::vec3(ctptr->get_position()[3]));
    cptr->setUp(glm::vec3(ctptr->get_transform()[1]));
     cptr->setDirection(glm::vec3(ctptr->get_rotation()[0]));
 	ccptr->update(delta_time);
}

void RenderingSystem::Run(const std::vector<std::shared_ptr<Entity>> &entities,double delta_time,std::shared_ptr<Entity> skyLight ){

    //Get enitities with mesh Component to render them
    std::vector<std::shared_ptr<Entity>> meshEntities = this->getEntitiesWithComponents<MeshRenderer, Transform>(entities);

    //Get camera Entities
    std::vector<std::shared_ptr<Entity>> cameraEntities = this->getEntitiesWithComponents<Camera, Transform, FlyCameraController>(entities);

    //Get lights componet
    std::vector<std::shared_ptr<Entity>> lights = this->getEntitiesWithComponents<Light, Transform>(entities);


    //Get meshRenderers
    std::vector<std::shared_ptr<MeshRenderer>> meshRenderers = this->getComponentVector<MeshRenderer>(entities);

    std::shared_ptr<SkyLight> sky_light = NULL;
    if(skyLight != NULL){
        sky_light = skyLight->getComp<SkyLight>();
    }
    //Taking the main camera which is the first index in the array
    cptr = cameraEntities[0]->getComp<Camera>();
    ctptr = cameraEntities[0]->getComp<Transform>();
    ccptr = cameraEntities[0]->getComp<FlyCameraController>();

    //Updating Camera position and Getting view Projection
    this->updateCameraPosition(delta_time);
	glm::mat4 viewProjection = cptr->getVPMatrix();

	//Create M
	std::vector<RenderObjects> objects;

    for (unsigned int x = 0; x < meshRenderers.size(); ++x)
    {
        std:: shared_ptr<Transform> tptr = meshRenderers[x]->getEntity()->getComp<Transform>();
        //Call this recursive function only on parent nodes
        if(tptr->get_parent() == nullptr)
            this->calculateDistance(objects,tptr,glm::mat4(1.0f),viewProjection);
    }
    std::sort(std::begin(objects), std::end(objects));

    for(int i=0; i<meshRenderers.size(); i++){


        std::shared_ptr<Material> materialPtr = meshRenderers[i]->getMaterial();
        std::shared_ptr<ShaderProgram> shaderProgram = materialPtr->getShaderProgram();
        glUseProgram(*shaderProgram);
        shaderProgram->set("camera_position", glm::vec3(ctptr->get_position()[3]));
        shaderProgram->set("view_projection",viewProjection);
        shaderProgram->set("sky_light.top_color", sky_light!=NULL&&sky_light->enabled ? sky_light->top_color : glm::vec3(0.0f));
        shaderProgram->set("sky_light.middle_color", sky_light!=NULL&&sky_light->enabled ? sky_light->middle_color : glm::vec3(0.0f));
        shaderProgram->set("sky_light.bottom_color", sky_light!=NULL&&sky_light->enabled ? sky_light->bottom_color : glm::vec3(0.0f));
        // We will go through all the lights and send the enabled ones to the shader.
        int light_index = 0;
        const int MAX_LIGHT_COUNT = 16;
        for(const auto& lightEntity : lights) {
            std::shared_ptr<Light> light = lightEntity->getComp<Light>();
            std::shared_ptr<Transform> lightTransform = lightEntity->getComp<Transform>();
            if(!light->enabled) continue;
            std::string prefix = "lights[" + std::to_string(light_index) + "].";

            shaderProgram->set(prefix + "type", static_cast<int>(light->lightType));
            shaderProgram->set(prefix + "color", light->color);
            switch (light->lightType) {
                case LightType::DIRECTIONAL:
                    shaderProgram->set(prefix + "direction", glm::normalize(lightTransform->get_rotation_vec()));
                    break;
                case LightType::POINT:
                    shaderProgram->set(prefix + "position", glm::vec3(lightTransform->get_position()[3]));
                    shaderProgram->set(prefix + "attenuation_constant", light->attenuation.constant);
                    shaderProgram->set(prefix + "attenuation_linear", light->attenuation.linear);
                    shaderProgram->set(prefix + "attenuation_quadratic", light->attenuation.quadratic);
                    break;
                case LightType::SPOT:
                    shaderProgram->set(prefix + "position", glm::vec3(lightTransform->get_position()[3]));
                    shaderProgram->set(prefix + "direction", glm::vec3(lightTransform->get_rotation_vec()));
                    shaderProgram->set(prefix + "attenuation_constant", light->attenuation.constant);
                    shaderProgram->set(prefix + "attenuation_linear", light->attenuation.linear);
                    shaderProgram->set(prefix + "attenuation_quadratic", light->attenuation.quadratic);
                    shaderProgram->set(prefix + "inner_angle", light->spot_angle.inner);
                    shaderProgram->set(prefix + "outer_angle", light->spot_angle.outer);
                    break;
            }
            light_index++;
            if(light_index >= MAX_LIGHT_COUNT) break;
            // Since the light array in the shader has a constant size, we need to tell the shader how many lights we sent.

        }
        shaderProgram->set("light_count", light_index);
    }
	//Start Drawing the screen
	//clear screen to draw next frame
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Looping on entities to draw the from parent to children nodes
//    for (unsigned int x = 0; x < meshEntities.size(); ++x)
//	{
//        std:: shared_ptr<Transform> tptr = meshEntities[x]->getComp<Transform>();
//		//Call this recursive function only on parent nodes
//        if(tptr->get_parent() == nullptr)
//            this->drawNode(tptr,glm::mat4(1.0f));
//    }
    for (unsigned int x = 0; x < objects.size(); ++x)
	{
        std::cout<< "ID:"<< objects[x].meshRenderer->getEntity()->getId()<<" "<< x <<std::endl;
        objects[x].meshRenderer->getEntity()->getComp<RenderState>()->update();
        objects[x].meshRenderer->renderMesh(objects[x].transform_matrix);
    }
    if(sky_light!=NULL){
        std::shared_ptr<MeshRenderer> meshRenderer= skyLight->getComp<MeshRenderer>();
        std::shared_ptr<Material> materialPtr = meshRenderer->getMaterial();
        std::shared_ptr<ShaderProgram> shaderProgram = materialPtr->getShaderProgram();
        glUseProgram(*shaderProgram);
        shaderProgram->set("camera_position", glm::vec3(ctptr->get_position()[3]));
        shaderProgram->set("view_projection",viewProjection);
        shaderProgram->set("sky_light.top_color", sky_light!=NULL&&sky_light->enabled ? sky_light->top_color : glm::vec3(0.0f));
        shaderProgram->set("sky_light.middle_color", sky_light!=NULL&&sky_light->enabled ? sky_light->middle_color : glm::vec3(0.0f));
        shaderProgram->set("sky_light.bottom_color", sky_light!=NULL&&sky_light->enabled ? sky_light->bottom_color : glm::vec3(0.0f));
        shaderProgram->set("exposure", 2.0f);
        skyLight->getComp<RenderState>()->culled_face=GL_FRONT; 
        skyLight->getComp<RenderState>()->update();
        meshRenderer->renderMesh(glm::mat4(0.0f));
    }
}
