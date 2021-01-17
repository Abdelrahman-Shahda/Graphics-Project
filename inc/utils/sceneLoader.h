//
// Created by 20101 on 1/17/2021.
//
#ifndef GRAPHICSPROJECT_SCENELOADER_H
#define GRAPHICSPROJECT_SCENELOADER_H

#include <iostream>
#include <json/json.hpp>
#include <fstream>

#include <resources/material.h>
#include <utils/loadingFunction.h>

using std::string;
using std::unordered_map;

class SceneLoader {

    nlohmann::json json;
	unordered_map<string, Resources::Material> materialsMap;

	void loadMaterial();

public:
    SceneLoader(std::string scenePath);



};
#endif //GRAPHICSPROJECT_SCENELOADER_H
