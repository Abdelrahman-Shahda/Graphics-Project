
//
// Created by Shaimaa on 11/29/2020.
// Naming Edited by Asfar 11/30/2020.
//

#ifndef GRAPHICSPROJECT_TRANSFORM_COMPONENT_HPP
#define GRAPHICSPROJECT_TRANSFORM_COMPONENT_HPP

#include <glm/glm.hpp>
class Transform{
private:
    glm::mat4 position;
    glm::mat4 Rotation;
    glm::mat4 scale;
    Transform* parent;
public:
    void set_position(glm::vec3 v);
    void set_rotation(glm::vec3 v);
    void set_scale(glm::vec3 v);
    void set_parent(Transform * transformComponent);
    glm::mat4 get_transform();
    glm::mat4 get_position();
    glm::mat4 get_rotation();
    glm::mat4 get_scale();
    Transform * get_parent();

};
#endif //GRAPHICSPROJECT_TRANSFORM_COMPONENT_HPP