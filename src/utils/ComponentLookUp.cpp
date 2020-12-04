//
// Created by 20101 on 12/4/2020.
//
#include <utils/ComponentLookUp.h>
std::unordered_map<std::type_index,ComponentType > ComponentLookUp::lookUpMap;
void ComponentLookUp::setUpMap() {

    //Set Up the map to fetch the type quickly
    ComponentLookUp::lookUpMap[typeid(Camera)] = ComponentType::CAMERA;
    ComponentLookUp::lookUpMap[typeid(FlyCameraController)] = ComponentType::CAMERACONTROLLER;
    ComponentLookUp::lookUpMap[typeid(MeshRenderer)] = ComponentType:: MESH_RENDERER;
    ComponentLookUp::lookUpMap[typeid(Transform)] = ComponentType::TRANSFORM;
}