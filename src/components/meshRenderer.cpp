#include <components/meshRenderer.h>
#include <iostream>

MeshRenderer::MeshRenderer(weak_ptr<Entity> entityPtr,shared_ptr<Mesh> meshPtr , shared_ptr<Material> materialPtr)
	:Component(entityPtr),meshPtr(meshPtr), materialPtr(materialPtr)
{
	type = MESH_RENDERER;
}

void MeshRenderer::renderMesh(glm::mat4 transform_matrix)
{
	std::shared_ptr<ShaderProgram> shaderProgram = materialPtr->getShaderProgram();
	glUseProgram(*shaderProgram);
    shaderProgram->set("transform", transform_matrix);
	materialPtr->passShaderParamters();
	meshPtr->draw();
}
