//
// Created by Shaimaa on 11/29/2020.
//
#include <glm/gtx/euler_angles.hpp>

#include "transform_component.hpp"
void transform_component::set_parent(transform_component *transformComponent) {parent=transformComponent;}
void transform_component::set_position(glm::vec3 v) {position= glm::translate(glm::mat4(1.0f),v);}
void transform_component::set_scale(glm::vec3 v) {scale=glm::scale(glm::mat4(1.0f),v);}
void transform_component::set_rotation(glm::vec3 v) {Rotation=glm::yawPitchRoll(v.y, v.x, v.z);}
transform_component * transform_component::get_parent(){return parent;}
glm::mat4 transform_component::get_final_position() {return position*scale*Rotation; }

