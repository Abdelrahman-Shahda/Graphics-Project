//
// Created by 20101 on 1/17/2021.
//
#include <glm/vec2.hpp>
#include <json/json.hpp>
#include <entity.hpp>
#ifndef GRAPHICSPROJECT_LOADINGFUNCTION_H
#define GRAPHICSPROJECT_LOADINGFUNCTION_H

#include <resources/shader.hpp>
#include <resources/sampler.h>

#include <glm/glm.hpp>
#include <json/json.hpp>

using std::shared_ptr;
using std::string;
using namespace Resources;



namespace glm {
    template<length_t L, typename T, qualifier Q>
    void from_json(const nlohmann::json& j, vec<L, T, Q>& v){
        for(length_t index = 0; index < L; ++index)
            v[index] = j[index].get<T>();
    }
}

#endif //GRAPHICSPROJECT_LOADINGFUNCTION_H
