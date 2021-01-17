//
// Created by 20101 on 1/17/2021.
//
#include <iostream>
#include <json/json.hpp>
#include <fstream>
#ifndef GRAPHICSPROJECT_SCENELOADER_H
#define GRAPHICSPROJECT_SCENELOADER_H

class SceneLoader {

    nlohmann::json json;
public:
    SceneLoader(std::string scenePath);



};
#endif //GRAPHICSPROJECT_SCENELOADER_H
