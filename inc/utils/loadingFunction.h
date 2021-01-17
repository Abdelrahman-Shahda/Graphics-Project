//
// Created by 20101 on 1/17/2021.
//

#ifndef GRAPHICSPROJECT_LOADINGFUNCTION_H
#define GRAPHICSPROJECT_LOADINGFUNCTION_H

#include <resources/shader.hpp>
#include <resources/sampler.h>

#include <glm/glm.hpp>
#include <json/json.hpp>

using std::shared_ptr;
using std::string;
using namespace Resources;

//Map of enums in order to facilate reading GLenums
static std::map<std::string, GLenum> const enumsTable = { {"GL_REPEAT",GL_REPEAT}, {"GL_MIRRORED_REPEAT",GL_MIRRORED_REPEAT},
	{"GL_CLAMP_TO_EDGE",GL_CLAMP_TO_EDGE},{"GL_CLAMP_TO_BORDER",GL_CLAMP_TO_BORDER}, {"GL_NEAREST",GL_NEAREST},{"GL_LINEAR",GL_LINEAR},
	{"GL_NEAREST_MIPMAP_NEAREST",GL_NEAREST_MIPMAP_NEAREST},{"GL_LINEAR_MIPMAP_NEAREST",GL_LINEAR_MIPMAP_NEAREST},
	{"GL_NEAREST_MIPMAP_LINEAR",GL_NEAREST_MIPMAP_LINEAR},{"GL_LINEAR_MIPMAP_LINEAR",GL_LINEAR_MIPMAP_LINEAR},{}
};


namespace glm {
    template<length_t L, typename T, qualifier Q>
    void from_json(const nlohmann::json& j, vec<L, T, Q>& v){
        for(length_t index = 0; index < L; ++index)
            v[index] = j[index].get<T>();
    }
}

shared_ptr<ShaderProgram> loadShader(const nlohmann::json& j);
shared_ptr<Sampler> loadSampler(const nlohmann::json& j);


#endif //GRAPHICSPROJECT_LOADINGFUNCTION_H
