#ifndef RENDERING___SYSTEM__H
#define RENDERING___SYSTEM__H

#include <systems/System.hpp>
#include <entity.hpp>
#include <memory>
struct RenderObjects {
    std::shared_ptr<MeshRenderer> meshRenderer;
    float distance;
    glm::mat4 transform_matrix;
};
class RenderingSystem : public System 
{
	//Private Member functions
    void drawNode(const std::shared_ptr<Transform>& node, const glm::mat4& parent_transform_matrix);
    void calculateDistance(std::vector<RenderObjects>& objects,const std::shared_ptr<Transform>& node, const glm::mat4& parent_transform_matrix, const glm::mat4& cameraVPMatrix);
    void updateCameraPosition(double delta_time);

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
