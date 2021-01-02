//
// Created by 20101 on 12/29/2020.
//
#include <components/lighting.h>

Light::Light(std::weak_ptr<Entity> entity, LightType ty, glm::vec3 col, bool en, float con, float line, float quad,
             float in, float ou):Component(entity) {
  type = ComponentType ::LIGHT;
  lightType = ty;
  color = col;
  enabled = en;
  attenuation.constant = con;
  attenuation.linear = line;
  attenuation.quadratic = quad;
  spot_angle.inner = in;
  spot_angle.outer = ou;


}
