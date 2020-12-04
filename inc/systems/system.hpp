#ifndef SYSTEM___H
#define SYSTEM___H

#include <vector>
#include <memory>
#include <entity.hpp>
class System
{
public:
    virtual void Run(const std::vector<std::shared_ptr<Entity>> entities)=0;

protected:
    template<class T>
    std::vector<std::shared_ptr<Entity>> getEntitiesByComponent(const std::vector<std::shared_ptr<Entity>> entities);

    template<class T, class ... rest>
    std::vector<std::shared_ptr<Entity>> getEntitiesByComponents(const std::vector<std::shared_ptr<Entity>> entities);
};

template<class T>
std::vector<std::shared_ptr<Entity>> System::getEntitiesByComponent(const std::vector<std::shared_ptr<Entity>> entities)
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

template<class T, class ... rest>
std::vector<std::shared_ptr<Entity>> System::getEntitiesByComponents(const std::vector<std::shared_ptr<Entity>> entities)
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
