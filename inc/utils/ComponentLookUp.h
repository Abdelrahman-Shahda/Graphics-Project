
#ifndef GRAPHICSPROJECT_COMPONENTLOOKUP_H
#define GRAPHICSPROJECT_COMPONENTLOOKUP_H

#include <components/component.h>
#include <components/camera.hpp>
#include <components/flyCameraController.hpp>
#include <components/meshRenderer.h>
#include <components/lighting.h>
#include "components/skyLight.h"
#include <components/renderState.hpp>

#include <unordered_map>
#include <typeindex>
#include <typeinfo>

class ComponentLookUp{

public:
    static void setUpMap();
    template<class T>
    static ComponentType lookUp();
private:
    static std::unordered_map<std::type_index,ComponentType > lookUpMap;
};

template <class T>
ComponentType ComponentLookUp::lookUp(){

    //If type is not found return default type
   if(lookUpMap.find(typeid(T)) != lookUpMap.end()){
       return lookUpMap[typeid(T)];
   }
   return ComponentType ::BASE;

}

#endif //GRAPHICSPROJECT_COMPONENTLOOKUP_H
