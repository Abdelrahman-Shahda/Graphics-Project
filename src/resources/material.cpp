#include "../../inc/resources/material.h"

using namespace Resources;

Material::Material(std::shared_ptr <ShaderProgram> shaderPtr) :shaderPtr(shaderPtr)
{
	//get max number of texture units
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnit);

	currentTextureUnit = 0;
	this->shaderPtr = shaderPtr;
}

Material::~Material()
{
	//deleting texture shader params
	for (auto itr = textureMapParameters.begin(); itr != textureMapParameters.end(); itr++)
		delete (*itr);

	for (auto itr = textureTintParameters.begin(); itr != textureTintParameters.end(); itr++)
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


void Material::addTexture(std::shared_ptr<Texture> texturePtr, std::shared_ptr<Sampler> samplerPtr, glm::vec3 tint)
{
	if (currentTextureUnit > maxTextureUnit)
	{
		std::cerr << "Error!! maximum number of textures reached!! \n";
		return;
	}

	texturePtrs.push_back(texturePtr);
	samplerPtrs.push_back(samplerPtr);

	//add new map shader param for texture with same name
	string paramName = "material."+texturePtr->name+"_map";
	textShaderParameter* shaderParamPtr= new textShaderParameter(paramName, currentTextureUnit);
	textureMapParameters.push_back(shaderParamPtr);
	
	//add new tint shader param for texture with same name
    string tintParam = "material."+ texturePtr->name+"_tint";
    ShaderParameter<glm::vec3>* tintParamPtr= new ShaderParameter<glm::vec3>(tintParam, tint);
	textureTintParameters.push_back(tintParamPtr);
    currentTextureUnit++;
}

void Material::passTexturesToShader()
{
	//Bind each texture then pass it to shader program
	for (int index=0; index< currentTextureUnit;index++)
	{
		GLuint currentUnit = GL_TEXTURE0 + index;
		texturePtrs[index]->useTexture(currentUnit);
		samplerPtrs[index]->useSampler(index);
		textureMapParameters[index]->setUinform(shaderPtr);
		textureTintParameters[index]->setUinform(shaderPtr);

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