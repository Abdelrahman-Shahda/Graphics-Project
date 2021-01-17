//
// Created by 20101 on 1/17/2021.
//
#include <utils/sceneLoader.h>
#include <utils/loadingFunction.h>
SceneLoader::SceneLoader(std::string scenePath) {

    std::ifstream file_in(scenePath);
    nlohmann::json json;
    file_in >> json;
    file_in.close();
    loadEntites(json["Scene"]);
//    std::cout << json["Scene"].dump(4) << std::endl;
}

void SceneLoader::loadEntites(nlohmann::json &json) {

    for(auto& [name, child]: json.items()){

        std::shared_ptr<Entity> entity(new Entity);
        std::string tag = child.value<std::string>("tag", "");
        entity->setTag(tag);
        std::cout << entity->withTag("Santa")<<std::endl;
    }

}