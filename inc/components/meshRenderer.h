#ifndef MESH__REDERER_H
#define MESH__REDERER_H

#include <memory>

#include "component.h"
#include "../resources/mesh.h"
#include "../resources/material.h"

using namespace Resources;
using std::shared_ptr;
using std::weak_ptr;

class MeshRenderer :public Component
{
	shared_ptr<Mesh> meshPtr;
	shared_ptr<Material> materialPtr;

public:
	MeshRenderer(weak_ptr<Entity> entityPtr,shared_ptr<Mesh> meshPtr=nullptr, shared_ptr<Material> materialPtr=nullptr);
	void renderMesh();

};
#endif // !MESH__REDERER_H