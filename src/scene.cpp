//
// Created by 20101 on 12/4/2020.
//

#include <scene.h>

bool Scene::addEntity(const std::shared_ptr<Entity> &newEntity) {
    entities.push_back(newEntity);
    return true;
}

bool Scene::deleteEntity(unsigned int id) {

    for(int i=0; i< entities.size();i++){
        if(id == entities[i]->getId()){
            entities.erase(entities.begin()+i);
            return true;
        }
    }
    return false;
}

const std::vector<std::shared_ptr<Entity>> & Scene::getEntities() {
    return entities;
}