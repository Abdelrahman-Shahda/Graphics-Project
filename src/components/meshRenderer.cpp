#include <components/meshRenderer.h>

MeshRenderer::MeshRenderer(weak_ptr<Entity> entityPtr,shared_ptr<Mesh> meshPtr , shared_ptr<Material> materialPtr)
	:Component(entityPtr),meshPtr(meshPtr), materialPtr(materialPtr)
{
	type = MESH_RENDERER;
}

void MeshRenderer::renderMesh(glm::mat4 transform_matrix)
{
	glUseProgram(*(materialPtr->getShaderProgram()));
	meshPtr->draw();
}
