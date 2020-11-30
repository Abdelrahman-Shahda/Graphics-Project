//
// Created by 20101 on 11/28/2020.
//

#ifndef GRAPHICSPROJECT_COMPONENTLOOKUP_H
#define GRAPHICSPROJECT_COMPONENTLOOKUP_H

#include <components/component.h>
#include <components/camera.hpp>
#include <components/flyCameraController.hpp>
#include <components/mesh.h>


#include <unordered_map>
#include <typeindex>
#include <typeinfo>

class ComponentLookUp{

public:
    static void setLookUpMap();
    template<class T>
    static ComponentType lookUp();
private:
    static std::unordered_map<std::type_index,ComponentType > lookUpMap;
};
std::unordered_map<std::type_index,ComponentType > ComponentLookUp::lookUpMap;
void ComponentLookUp::setLookUpMap() {

    //Set Up the map to fetch the type quickly
    ComponentLookUp::lookUpMap[typeid(Camera)] = ComponentType::CAMERA;
    ComponentLookUp::lookUpMap[typeid(FlyCameraController)] = ComponentType::CAMERACONTROLLER;
	ComponentLookUp::lookUpMap[typeid(Mesh)] = ComponentType:: MESH;
    ComponentLookUp::lookUpMap[typeid(Transform)] = ComponentType:: TRANSFORM;
}
template <class T>
ComponentType ComponentLookUp::lookUp(){

    //If type is not found return default type
   if(lookUpMap.find(typeid(T)) != lookUpMap.end()){
       return lookUpMap[typeid(T)];
   }
   return ComponentType ::BASE;

}

#endif //GRAPHICSPROJECT_COMPONENTLOOKUP_H
