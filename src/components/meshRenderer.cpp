#include "../../inc/components/meshRenderer.h"

MeshRenderer::MeshRenderer(weak_ptr<Entity> entityPtr,shared_ptr<Mesh> meshPtr , shared_ptr<Material> materialPtr)
	:Component(entityPtr),meshPtr(meshPtr), materialPtr(materialPtr)
{
	type = MESH_RENDERER;
}

void MeshRenderer::renderMesh()
{
	glUseProgram(*(materialPtr->getShaderProgram()));
	//TODO:: pass necessary params (now placed in shader.hpp)

	//Draw the mesh
	meshPtr->draw();
}
