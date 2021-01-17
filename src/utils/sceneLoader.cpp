//
// Created by 20101 on 1/17/2021.
//
#include <utils/sceneLoader.h>

SceneLoader::SceneLoader(std::string scenePath) {

    std::ifstream file_in(scenePath);
    file_in >> json;
    file_in.close();
    std::cout << json.dump(4) << std::endl;
	loadMaterial();
}

void SceneLoader::loadMaterial()
{
	nlohmann::json resources=json["resources"];
	std::cout << resources["shaders"];

	unordered_map<string, shared_ptr<Resources::ShaderProgram>> shadersMap;
	for (auto &[name,shader] : resources["shaders"].items())
	{
		shared_ptr<Resources::ShaderProgram> shaderProgram=loadShader(shader);
		shadersMap[name] = shaderProgram;
	}
}