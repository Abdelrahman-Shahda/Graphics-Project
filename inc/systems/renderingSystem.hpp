#ifndef RENDERING___SYSTEM__H
#define RENDERING___SYSTEM__H

#include "system.hpp"
#include <memory>


class RenderingSystem : public System 
{
    void Run(const std::vector<std::shared_ptr<Entity>> enitities);

    std::shared_ptr<MeshRenderer> mcptr;
    std::shared_ptr<Transform> mtptr;

    std::shared_ptr<Camera> cptr;
    std::shared_ptr<Transform> ctptr;
    std::shared_ptr<FlyCameraController> ccptr;
};

#endif // !RENDERING___SYSTEM__H
