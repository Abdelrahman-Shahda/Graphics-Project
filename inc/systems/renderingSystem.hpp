#ifndef RENDERING___SYSTEM__H
#define RENDERING___SYSTEM__H

#include <systems/System.hpp>
#include <entity.hpp>
#include <memory>
#include <algorithm>

struct RenderObjects {
    std::shared_ptr<MeshRenderer> meshRenderer;
    float distance;
    glm::mat4 transform_matrix;

    bool operator<(const RenderObjects& other) const {
        std::shared_ptr<RenderState> myRenderState = meshRenderer->getEntity()->getComp<RenderState>();
        std::shared_ptr<RenderState> otherRenderState = other.meshRenderer->getEntity()->getComp<RenderState>();

        // Let opaque objects be drawn before the transparent ones
        if(myRenderState->enable_blending != otherRenderState->enable_blending) return myRenderState->enable_blending < otherRenderState->enable_blending;
            // If both are transparent, sort from farthest to nearest
        else if(myRenderState->enable_blending) return distance > other.distance;
            // If both are opaque, sort from nearest to farthest
        else return distance < other.distance;
    }
};

class RenderingSystem : public System 
{
	//Private Member functions
    void calculateDistance(std::vector<RenderObjects>& objects,const std::shared_ptr<Transform>& node, const glm::mat4& parent_transform_matrix, const glm::mat4& cameraVPMatrix);
    void calculateCameraTransform();
    void updateCameraPosition(double delta_time);
    void setLightParamters(const std::vector<std::shared_ptr<MeshRenderer>>& meshRenderers, glm::vec3 cameraPosition,glm::mat4 viewProjection,std::shared_ptr<SkyLight> sky_light,const  std::vector<std::shared_ptr<Entity>> &lights);
	//Data Members
    std::shared_ptr<MeshRenderer> mcptr;
    std::shared_ptr<Transform> mtptr;

    std::shared_ptr<Camera> cptr;
    std::shared_ptr<Transform> ctptr;
    std::shared_ptr<FlyCameraController> ccptr;

public:
    void Run(const std::vector<std::shared_ptr<Entity>> &enitities, double delta_time,std::shared_ptr<Entity> skyLight =NULL) override;

};

#endif // !RENDERING___SYSTEM__H
