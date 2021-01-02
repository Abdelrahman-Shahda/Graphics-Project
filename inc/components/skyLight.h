//
// Created by 20101 on 1/2/2021.
//

#ifndef GRAPHICSPROJECT_SKYLIGHT_H
#define GRAPHICSPROJECT_SKYLIGHT_H
#include "components/component.h"
#include <glm/glm.hpp>

class SkyLight :public Component{

public:

    SkyLight(std::weak_ptr<Entity> entity,
          bool en = true,
          glm::vec3 tp = {0,0,0},
          glm::vec3 md = {0,0,0},
          glm::vec3 bt = {0,0,0}
          );


    bool enabled;
    glm::vec3 top_color, middle_color, bottom_color;

};
#endif //GRAPHICSPROJECT_SKYLIGHT_H
