#ifndef SYSTEM___H
#define SYSTEM___H

#include <vector>
#include <memory>
#include <entity.hpp>
class System
{
public:
    virtual void Run(const std::vector<std::shared_ptr<Entity>> &entities,double delta_time, std::shared_ptr<Entity> skyLight =NULL)=0;

protected:
    template<class T>
    std::vector<std::shared_ptr<Entity>> getEntitiesWithComponent(const std::vector<std::shared_ptr<Entity>> &entities);

    template<class T, class ... rest>
    std::vector<std::shared_ptr<Entity>> getEntitiesWithComponents(const std::vector<std::shared_ptr<Entity>> &entities);

    template<class T>
    std::vector<std::shared_ptr<T>> getComponentVector(const std::vector<std::shared_ptr<Entity>> &entities);
};

template<class T>
std::vector<std::shared_ptr<Entity>> System::getEntitiesWithComponent(const std::vector<std::shared_ptr<Entity>> &entities)
{
    std::vector<std::shared_ptr<Entity>> temp;
    for (unsigned int x = 0; x < entities.size(); ++x)
    {
        if (entities[x]->hasComps<T>())
        {
            temp.push_back(entities[x]);
        }
    }
    return temp;
}
template<class T>
std::vector<std::shared_ptr<T>> System::getComponentVector(const std::vector<std::shared_ptr<Entity>> &entities){
    std::vector<std::shared_ptr<T>> temp;
    for (unsigned int x = 0; x < entities.size(); ++x)
    {
        if (entities[x]->hasComps<T>())
        {
            temp.push_back(entities[x]->getComp<T>());
        }
    }
    return temp;

}
template<class T, class ... rest>
std::vector<std::shared_ptr<Entity>> System::getEntitiesWithComponents(const std::vector<std::shared_ptr<Entity>> &entities)
{
    std::vector<std::shared_ptr<Entity>> temp;
    for (unsigned int x = 0; x < entities.size(); ++x)
    {
        if (entities[x]->hasComps<T, rest ...>())
        {
            temp.push_back(entities[x]);
        }
    }
    return temp;
}


#endif // !SYSTEM___H
