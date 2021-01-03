#ifndef MATERIAL__H
#define MATERIAL__H

#include <resources/shader.hpp>
#include <resources/shaderParameter.hpp>
#include <resources/texture.h>

#include <memory>
#include <vector>
#include <string>

namespace Resources {
	typedef  ShaderParameter<GLint> textShaderParameter;

	class Material
	{
		GLint currentTextureUnit;
		GLint maxTextureUnit;
        bool transparent;
		std::shared_ptr<ShaderProgram> shaderPtr;
		std::vector<std::shared_ptr<ShaderParameterBaseClass>> shaderParameters;
        std::vector<ShaderParameter<glm::vec3>*> textTintParameters;
		std::vector<textShaderParameter*> textureShaderParameters;
		std::vector< std::shared_ptr<Texture>> texturePtrs;

	public:
		Material(std::shared_ptr <ShaderProgram> shaderPtr = nullptr,bool trans = false);
		~Material();

		//Shader Program
		void setShaderProgram(std::shared_ptr <ShaderProgram> shaderPtr);
		std::shared_ptr <ShaderProgram> getShaderProgram();

		//Shader Params
		void addShaderParameter(std::shared_ptr<ShaderParameterBaseClass> param);
		void setAllShaderParameters(string name);
		bool setShaderParameter(string name);

		//Textures
		void addTexture(std::shared_ptr<Texture>, glm::vec3 tint = {1.0f, 1.0f, 1.0f});
		void passTexturesToShader();
	};

	
}


#endif // !MATERIAL__H
