#include <components/meshRenderer.h>


MeshRenderer::MeshRenderer(weak_ptr<Entity> entityPtr,shared_ptr<Mesh> meshPtr , shared_ptr<Material> materialPtr)
	:Component(entityPtr),meshPtr(meshPtr), materialPtr(materialPtr)
{
	type = MESH_RENDERER;
}	

void MeshRenderer::renderMesh(glm::mat4 transform_matrix)
{
	//Drawing Mesh
	std::shared_ptr<ShaderProgram> shaderProgram = materialPtr->getShaderProgram();
	glUseProgram(*shaderProgram);
    shaderProgram->set("object_to_world_inv_transpose", glm::inverse(transform_matrix), true);
    shaderProgram->set("object_to_world", transform_matrix);
	materialPtr->passTexturesToShader();
	materialPtr->setAllShaderParameters();
	meshPtr->draw();

	//Setting Bounding box of mesh
	maxBoundingBox = transform_matrix * glm::vec4(meshPtr->getMaxPoint(),0);
	minBoundingBox = transform_matrix * glm::vec4(meshPtr->getMinPoint(), 0);
}

shared_ptr<Material> MeshRenderer::getMaterial() {
    return materialPtr;
};

void MeshRenderer::setDepth(float dis) {
    depth = dis;
}

glm::vec3 MeshRenderer::getMaxBoundingBox()
{
	return maxBoundingBox;
}

glm::vec3 MeshRenderer::getMinBoundingBox()
{
	return minBoundingBox;
}