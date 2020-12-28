#include "../../inc/resources/material.h"

using namespace Resources;

Material::Material(std::shared_ptr <ShaderProgram> shaderPtr) :shaderPtr(shaderPtr)
{
	//get max number of texture units
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnit);
	maxTextureUnit =maxTextureUnit +GL_TEXTURE0 -1;

	currentTextureUnit = GL_TEXTURE0;
	this->shaderPtr = shaderPtr;
}

Material::~Material()
{
	//deleting texture shader params
	for (auto itr = textureShaderParameters.begin(); itr != textureShaderParameters.end(); itr++)
		delete (*itr);
}
 void Material::setShaderProgram(std::shared_ptr < ShaderProgram> shaderPtr)
{
	this->shaderPtr = shaderPtr;
}

std::shared_ptr <ShaderProgram> Material:: getShaderProgram()
{
	return shaderPtr;
}

void Material::addShaderParameter(std::shared_ptr<ShaderParameterBaseClass> param)
{
	shaderParameters.push_back(param);
}

void Material::addTexture(std::shared_ptr<Texture> texturePtr)
{
	if (currentTextureUnit > maxTextureUnit)
	{
		std::cerr << "Error!! maximum number of textures reached!! \n";
		return;
	}

	texturePtrs.push_back(texturePtr);

	//add new shaderParam with same name
	string paramName = texturePtr->name+"_map";
	textShaderParameter* shaderParamPtr= new textShaderParameter(paramName, currentTextureUnit);
	textureShaderParameters.push_back(shaderParamPtr);
	currentTextureUnit++;
}

void Material::passTexturesToShader()
{
	//Bind each texture then pass it to shader program
	for (int index=0; index<textureShaderParameters.size();index++)
	{
		texturePtrs[index]->useTexture(GL_TEXTURE0+ index);
		textureShaderParameters[index]->setUinform(shaderPtr);
	}
}

bool Material::setShaderParameter(string name)
{
	for (auto iterator = this->shaderParameters.begin(); iterator != this->shaderParameters.end(); iterator++)
	{
		if ((*iterator)->name == name)
		{
			(*iterator)->setUinform(shaderPtr);
			return true;
		}
	}
	return false;
}

void Material::setAllShaderParameters(string name)
{
	for (auto iterator = this->shaderParameters.begin(); iterator != this->shaderParameters.end(); iterator++)
		(*iterator)->setUinform(shaderPtr);
}