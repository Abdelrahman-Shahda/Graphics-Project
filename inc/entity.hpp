#ifndef ENTITY___H
#define ENTITY___H


#include "components/component.h"
#include "utils/ComponentLookUp.h"
#include <memory>
#include <vector>
#include <bitset>

class Entity: std::enable_shared_from_this<Entity>
{
    std::bitset<ComponentType::COUNT> isComps;
    std::vector<std::shared_ptr<Component>> comps;


public:
    template<class T>
	bool hasComp();

    template<class T, class ...Args>
    std::shared_ptr<T> addComp(Args...args);

    template<class T>
    bool removeComp();

    template<class T>
    std::shared_ptr<T> getComp();

};

template<class T>
bool Entity::hasComp() {
    return isComps.test(ComponentLookUp::lookUp<T>());
}

template<class T>
std::shared_ptr<T> Entity::getComp(){

    if(hasComp<T>()){
        ComponentType type = ComponentLookUp::lookUp<T>();

        for(int i = 0; i < (int)comps.size(); i++){
            if(comps[i]->type == type)
                return  comps[i];
        }
    }
    return NULL;
}
template<class T>
bool Entity::removeComp(){

    if(hasComp<T>()){
        //If it exists get the type to be removed and reset it in isComps and erase it form comps vector
        ComponentType  typeToBeRemoved = ComponentLookUp::lookUp<T>();

        for(int i = 0; i< comps.size(); i++){

            if(comps[i] -> type == typeToBeRemoved){
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
    if(hasComp<T>())
        return NULL;

    //Create new component and set its bit in isComps and Add it in comps Vector
    std::shared_ptr<T> newComp = std::make_shared<T>(weak_from_this(), args...);
    isComps.set(newComp->type);
    comps.push_back(newComp);
    return newComp;
}

#endif /*ENTITY___H*/