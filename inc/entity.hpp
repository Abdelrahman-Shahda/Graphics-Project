#ifndef ENTITY___H
#define ENTITY___H


#include "components/component.h"
#include "utils/ComponentLookUp.h"
#include <memory>
#include <vector>
#include <bitset>

class Entity: public std::enable_shared_from_this<Entity>
{
    std::bitset<ComponentType::COUNT> isComps;
    static unsigned int next_id;
    unsigned int id;
    std::vector<std::shared_ptr<Component>> comps;
    Entity(const Entity&); //disallow copy constructor
    Entity& operator=(const Entity&);//disallow assignment
public:
    Entity();
    unsigned int getId();
    template<class T>
	bool hasComps();

    template<class T1, class T2, class ...Rest>
    bool hasComps();

    template<class T, class ...Args>
    std::shared_ptr<T> addComp(Args...args);

    template<class T>
    bool removeComp();

    template<class T>
    std::shared_ptr<T> getComp();

};


template<class T>
bool Entity::hasComps() {
    return isComps.test(ComponentLookUp::lookUp<T>());
}

template<class T1, class T2, class ...Rest>
bool Entity::hasComps(){

    if(isComps.test(ComponentLookUp::lookUp<T1>())){
        return hasComps<T2,Rest...>();
    }
    return false;
}

template<class T>
std::shared_ptr<T> Entity::getComp(){

    if(hasComps<T>()){
        ComponentType type = ComponentLookUp::lookUp<T>();
        for(int i = 0; i < (int)comps.size(); i++){
            if(comps[i]->getType() == type)
                return std::static_pointer_cast<T>(comps[i]);
        }
    }
    return NULL;
}
template<class T>
bool Entity::removeComp(){

    if(hasComps<T>()){
        //If it exists get the type to be removed and reset it in isComps and erase it form comps vector
        ComponentType  typeToBeRemoved = ComponentLookUp::lookUp<T>();

        for(int i = 0; i< comps.size(); i++){

            if(comps[i]->getType() == typeToBeRemoved){
                comps.erase(comps.begin()+i);
                isComps.reset(typeToBeRemoved);
                return true;
            }
        }

    }
    return false;
}

template<class T, class ...Args>
std::shared_ptr<T> Entity::addComp(Args...args){

    //If Comp exists return Null
    if(hasComps<T>())
        return NULL;

    //Create new component and set its bit in isComps and Add it in comps Vector
    std::shared_ptr<T> newComp = std::make_shared<T>(this->weak_from_this(), args...);
    isComps.set(newComp->getType());
    comps.push_back(newComp);
    return newComp;
}

#endif /*ENTITY___H*/
