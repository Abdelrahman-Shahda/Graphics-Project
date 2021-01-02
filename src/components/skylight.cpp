//
// Created by 20101 on 12/29/2020.
//
#include <components/skyLight.h>

SkyLight::SkyLight(std::weak_ptr<Entity> entity,bool en, glm::vec3 tp , glm::vec3 md , glm::vec3 bt  ):Component(entity)
{
    type = ComponentType::SKYLIGHT;
    enabled = en;
    top_color = tp;
    middle_color = md;
    bottom_color = bt;

}
