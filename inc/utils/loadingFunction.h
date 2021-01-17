//
// Created by 20101 on 1/17/2021.
//

#ifndef GRAPHICSPROJECT_LOADINGFUNCTION_H
#define GRAPHICSPROJECT_LOADINGFUNCTION_H


namespace glm {
    template<length_t L, typename T, qualifier Q>
    void from_json(const nlohmann::json& j, vec<L, T, Q>& v){
        for(length_t index = 0; index < L; ++index)
            v[index] = j[index].get<T>();
    }
}

#endif //GRAPHICSPROJECT_LOADINGFUNCTION_H
