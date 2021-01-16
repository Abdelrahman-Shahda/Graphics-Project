#include <systems/system.hpp>

std::shared_ptr<Entity> System::getEntityWithTag(const std::vector<std::shared_ptr<Entity>> &entities,
                                                 std::string tag) {

    for(int i = 0; i<entities.size();i++){
        if(entities[i]->withTag(tag))
            return entities[i];
    }
    return NULL;
}
std::vector<std::shared_ptr<Entity>> System::getEntitiesWithTag(const std::vector<std::shared_ptr<Entity>> &entities,
                                                                std::string tag) {
    std::vector<std::shared_ptr<Entity>> temp;
    for (unsigned int x = 0; x < entities.size(); ++x)
    {
        if (entities[x]->withTag(tag))
        {
            temp.push_back(entities[x]);
        }
    }
    return temp;
}