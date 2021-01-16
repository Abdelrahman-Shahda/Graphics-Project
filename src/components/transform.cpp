//
// Created by Shaimaa on 11/29/2020.
// Naming Edited by Asfar 11/30/2020.
//
#include <glm/gtx/euler_angles.hpp>
#include <components/transform.h>
#include <vector>

Transform::Transform(std::weak_ptr<Entity> entity,glm::vec3 p, glm::vec3 r, glm::vec3 s):Component(entity)
{
    type = TRANSFORM;
    set_rotation(r);
    set_scale(s);
    set_position(p);
    parent = nullptr;
}
void Transform::update(){transform=position*glm::yawPitchRoll(rotation.y,rotation.x,rotation.z)*scale;}
void Transform::set_parent(std::shared_ptr<Transform> transformComponent) {parent=transformComponent;}
void Transform::set_position(glm::vec3 v) {position= glm::translate(glm::mat4(1.0f),v);}
void Transform::set_scale(glm::vec3 v) {scale=glm::scale(glm::mat4(1.0f),v);}
void Transform::set_rotation(glm::vec3 v) {rotation=v;}
void Transform::set_transform(glm::mat4 v) {transform=v;}

void Transform::add_child(std::shared_ptr<Transform> transformComponent){children.push_back(transformComponent);}
std::shared_ptr<Transform> Transform::get_parent(){return parent;}
std::vector<std::shared_ptr<Transform>> Transform::get_children(){return children;}
glm::mat4 Transform::get_transform() {return transform;}
glm::mat4 Transform::get_position() { return position;}

glm::mat4 Transform::get_rotation() { return glm::yawPitchRoll(rotation.y,rotation.x,rotation.z);}
glm::vec3 Transform::get_rotation_vec() {return rotation;}

glm::mat4 Transform::get_ModalMatrix() {
    if(parent != NULL)
        return parent->get_ModalMatrix() * transform;
    else
        return transform;
}