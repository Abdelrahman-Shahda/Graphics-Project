
//
// Created by Shaimaa on 11/29/2020.
// Naming Edited by Asfar 11/30/2020.
// Inherited from Component by Asfar 11/30/2020
//

#ifndef GRAPHICSPROJECT_TRANSFORM_COMPONENT_HPP
#define GRAPHICSPROJECT_TRANSFORM_COMPONENT_HPP
#include <glm/glm.hpp>
#include <memory>
#include <components/component.h>
#include <vector>

class Transform : public Component{
private:
    glm::mat4 position;
    glm::vec3 rotation;
    glm::mat4 scale;
    Transform* parent;
    std::vector<std::shared_ptr<Transform>> children;
public:
    Transform(std::weak_ptr<Entity> entity,glm::vec3 p, glm::vec3 r, glm::vec3 s);

    void set_position(glm::vec3 v);
    void set_rotation(glm::vec3 v);
    void set_scale(glm::vec3 v);
    void set_parent(Transform * transformComponent);
    glm::mat4 get_transform();
    glm::mat4 get_position();
    glm::mat4 get_rotation();
    glm::vec3 get_rotation_vec();
    Transform* get_parent();
    std::vector<std::shared_ptr<Transform>> get_children();

};
#endif //GRAPHICSPROJECT_TRANSFORM_COMPONENT_HPP