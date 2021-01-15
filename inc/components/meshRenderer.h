#ifndef MESH__REDERER_H
#define MESH__REDERER_H

#include <memory>
#include <iostream>
#include <components/component.h>
#include <resources/mesh.hpp>
#include <resources/material.h>

using namespace Resources;
using std::shared_ptr;
using std::weak_ptr;

class MeshRenderer :public Component
{
	shared_ptr<Mesh> meshPtr;
	shared_ptr<Material> materialPtr;
    float depth;
	glm::vec3 maxBoundingBox;
	glm::vec3 minBoundingBox;

public:
	MeshRenderer(weak_ptr<Entity> entityPtr,shared_ptr<Mesh> meshPtr=nullptr, shared_ptr<Material> materialPtr=nullptr);
	void renderMesh(glm::mat4 transform_matrix);
    shared_ptr<Material> getMaterial();
    void setDepth(float dis);
	glm::vec3 getMaxBoundingBox();
	glm::vec3 getMinBoundingBox();
};
#endif // !MESH__REDERER_H
