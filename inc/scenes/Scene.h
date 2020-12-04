//
// Created by 20101 on 12/4/2020.
//

#ifndef GRAPHICSPROJECT_SCENE_H
#define GRAPHICSPROJECT_SCENE_H
#include <vector>
#include <memory>
#include <entity.hpp>
class Scene{
    std::vector<std::shared_ptr<Entity>> entities;
public:

    void addEntity(const std::shared_ptr<Entity> &newEntity);
    void deleteEntity(unsigned int id);
    const std::vector<std::shared_ptr<Entity>>& getEntities();
};
#endif //GRAPHICSPROJECT_SCENE_H
