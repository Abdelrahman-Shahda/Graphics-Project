//
// Created by 20101 on 1/17/2021.
//
#include <utils/sceneLoader.h>

SceneLoader::SceneLoader(std::string scenePath) {

    std::ifstream file_in(scenePath);
    nlohmann::json json;
    file_in >> json;
    file_in.close();
    std::cout << json.dump(4) << std::endl;
}
