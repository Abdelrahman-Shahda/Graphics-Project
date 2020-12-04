#ifndef RENDERING___SYSTEM__H
#define RENDERING___SYSTEM__H

#include "system.hpp"
#include <memory>


class RenderingSystem : public System 
{


    std::shared_ptr<MeshRenderer> mcptr;
    std::shared_ptr<Transform> mtptr;

    std::shared_ptr<Camera> cptr;
    std::shared_ptr<Transform> ctptr;
    std::shared_ptr<FlyCameraController> ccptr;
public:
    void Run(const std::vector<std::shared_ptr<Entity>> enitities);
    void drawNode(const std::shared_ptr<Transform>& node, const glm::mat4& parent_transform_matrix);
};

#endif // !RENDERING___SYSTEM__H
