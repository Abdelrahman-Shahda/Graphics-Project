//
// Created by 20101 on 1/17/2021.
//
#ifndef GRAPHICSPROJECT_SCENELOADER_H
#define GRAPHICSPROJECT_SCENELOADER_H

#include <iostream>
#include <json/json.hpp>
#include <fstream>

#include <resources/material.h>
#include <resources/mesh.hpp>
#include <components/player.hpp>

#include <utils/loadingFunction.h>
#include <utils/mesh-utils.hpp>

using std::string;
using std::unordered_map;

//Map of enums in order to facilate reading GLenums
static std::map<std::string, GLenum> const enumsTable = { {"GL_REPEAT",GL_REPEAT}, {"GL_MIRRORED_REPEAT",GL_MIRRORED_REPEAT},
	{"GL_CLAMP_TO_EDGE",GL_CLAMP_TO_EDGE},{"GL_CLAMP_TO_BORDER",GL_CLAMP_TO_BORDER}, {"GL_NEAREST",GL_NEAREST},{"GL_LINEAR",GL_LINEAR},
	{"GL_NEAREST_MIPMAP_NEAREST",GL_NEAREST_MIPMAP_NEAREST},{"GL_LINEAR_MIPMAP_NEAREST",GL_LINEAR_MIPMAP_NEAREST},
	{"GL_NEAREST_MIPMAP_LINEAR",GL_NEAREST_MIPMAP_LINEAR},{"GL_LINEAR_MIPMAP_LINEAR",GL_LINEAR_MIPMAP_LINEAR},{}
};


class SceneLoader {

    nlohmann::json json;
	unordered_map<string, shared_ptr<Resources::Material>> materialsMap;
	unordered_map<string, shared_ptr<Resources::Mesh>> meshesMap;

	void loadMaterial();
	shared_ptr<ShaderProgram> loadShader(const nlohmann::json& j);
	shared_ptr<Sampler> loadSampler(const nlohmann::json& j);
	shared_ptr<Mesh> loadMesh(const nlohmann::json&j);
	shared_ptr<Texture> loadTexture(nlohmann::json &j);
	void loadEntites( Application* application,nlohmann::json &json, std::shared_ptr<Transform> parent,std::vector<std::shared_ptr<Entity>> &entities);
public:
    SceneLoader(std::string scenePath);


    void loadComponent(std::string component,nlohmann::json& json, std::shared_ptr<Entity> en,Application* application,std::vector<std::shared_ptr<Entity>> &entities);
    std::vector<std::shared_ptr<Entity>> loadEntities(Application* application);
    shared_ptr<Entity> loadSky();
};
#endif //GRAPHICSPROJECT_SCENELOADER_H
