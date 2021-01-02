//
// Created by 20101 on 12/29/2020.
//

#ifndef GRAPHICSPROJECT_LIGHTING_H
#define GRAPHICSPROJECT_LIGHTING_H
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <components/component.h>
enum class LightType {
    DIRECTIONAL,
    POINT,
    SPOT
};

class Light :public Component{

public:

    Light(std::weak_ptr<Entity> entity,
          LightType ty  = LightType::POINT,
          glm::vec3 col = {1,1,1},
          bool en = true,
          float con =0.0f,
          float line = 0.0f,
          float quad = 0.0f,
          float in =glm::quarter_pi<float>(),
          float ou = glm::half_pi<float>());
    // Here we define our light. First member specifies its type.
    LightType lightType;

    // We will use this to enable/disable the light. If it is disabled. we won't send it to the shader.
    bool enabled;

    //Color of the light
    glm::vec3 color;

    // This affects how the light will dim out as we go further from the light.
    // The formula is light_received = light_emitted / (a*d^2 + b*d + c) where a, b, c are the quadratic, linear and constant factors respectively.
    struct {
        float constant, linear, quadratic;
    } attenuation; // Used for Point and Spot Lights only

    // This specifies the inner and outer cone of the spot light.
    // The light power is 0 outside the outer cone, the light power is full inside the inner cone.
    // The light power is interpolated in between the inner and outer cone.
    struct {
        float inner, outer;
    } spot_angle; // Used for Spot Lights only
};

#endif //GRAPHICSPROJECT_LIGHTING_H
