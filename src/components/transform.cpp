//
// Created by Shaimaa on 11/29/2020.
// Naming Edited by Asfar 11/30/2020.
//
#include <glm/gtx/euler_angles.hpp>
#include <components/transform.h>
void Transform:set_parent(transform_component *transformComponent) {parent=transformComponent;}
void Transfrom::set_position(glm::vec3 v) {position= glm::translate(glm::mat4(1.0f),v);}
void Transform::set_scale(glm::vec3 v) {scale=glm::scale(glm::mat4(1.0f),v);}
void Transform::set_rotation(glm::vec3 v) {Rotation=glm::yawPitchRoll(v.y, v.x, v.z);}
Transform * Transform::get_parent(){return parent;}
glm::mat4 Transform::get_transform() {return position*scale*Rotation; }

