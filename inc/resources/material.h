#ifndef MATERIAL__H
#define MATERIAL__H

#include <resources/shader.hpp>
#include <resources/shaderParameter.hpp>
#include <resources/texture.h>
#include <resources/sampler.h>

#include <memory>
#include <vector>
#include <string>

namespace Resources {
	typedef  ShaderParameter<GLint> textShaderParameter;

	class Material
	{
		std::vector<std::shared_ptr<ShaderParameterBaseClass>> shaderParameters;
		std::shared_ptr<ShaderProgram> shaderPtr;
		bool transparent;

		//Textures
		GLint currentTextureUnit;
		GLint maxTextureUnit;
        std::vector<ShaderParameter<glm::vec3>*> textureTintParameters;
		std::vector<textShaderParameter*> textureMapParameters;
		std::vector< std::shared_ptr<Texture>> texturePtrs;
		std::vector< std::shared_ptr<Sampler>> samplerPtrs;

	public:
		Material(std::shared_ptr <ShaderProgram> shaderPtr = nullptr,bool trans = false);
		~Material();

		//Shader Program
		void setShaderProgram(std::shared_ptr <ShaderProgram> shaderPtr);
		std::shared_ptr <ShaderProgram> getShaderProgram();

		//Shader Params
		void addShaderParameter(std::shared_ptr<ShaderParameterBaseClass> param);
		void setAllShaderParameters();
		bool setShaderParameter(string name);

		//Textures
		void addTexture(std::shared_ptr<Texture>, std::shared_ptr<Sampler> ,glm::vec3 tint = {1.0f, 1.0f, 1.0f});
		void passTexturesToShader();
	};

	
}


#endif // !MATERIAL__H
