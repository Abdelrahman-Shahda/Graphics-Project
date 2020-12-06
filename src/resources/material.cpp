#include "../../inc/resources/material.h"

using namespace Resources;

Material::Material(std::shared_ptr <ShaderProgram> shaderPtr) :shaderPtr(shaderPtr)
{
 this->shaderPtr = shaderPtr;
}

 void Material::setShaderProgram(std::shared_ptr < ShaderProgram> shaderPtr)
{
this->shaderPtr = shaderPtr;
}

std::shared_ptr <ShaderProgram> Material:: getShaderProgram()
{
	return shaderPtr;
}

void Material::passShaderParamters()
{
	for (auto iterator = this->shaderParameters.begin(); iterator != this->shaderParameters.end() ;iterator++)
	{
		(*iterator)->setUinform(shaderPtr);
	}
}

void Material::addShaderParameter(std::shared_ptr<ShaderParameter> param)
{
	shaderParameters.push_back(param);
}
