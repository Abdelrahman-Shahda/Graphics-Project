#include "../../inc/resources/material.h"
using namespace Resources;

Material::Material(std::shared_ptr <ShaderProgram> shaderPtr) :shaderPtr(shaderPtr)
{
}

 void Material::setShaderProgram(std::shared_ptr < ShaderProgram> shaderPtr)
{
	shaderPtr = shaderPtr;
}

std::shared_ptr <ShaderProgram> Material:: getShaderProgram()
{
	return shaderPtr;
}

void Material::passShaderParamters()
{
	for (auto iterator = this->shaderParameters.begin(); iterator != this->shaderParameters.end() ;iterator++)
	{
		iterator->setUinform(shaderPtr);
	}
}

