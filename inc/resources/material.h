#ifndef MATERIAL__H
#define MATERIAL__H

#include <resources/shader.hpp>
#include <resources/shaderParameter.hpp>
#include <memory>
#include <vector>
#include <string>

namespace Resources {

	class Material
	{
		std::shared_ptr<ShaderProgram> shaderPtr;
		std::vector<std::shared_ptr<ShaderParameter>> shaderParameters;

	public:
		Material(std::shared_ptr <ShaderProgram> shaderPtr = nullptr);

		//Shader Program
		void setShaderProgram(std::shared_ptr <ShaderProgram> shaderPtr);
		std::shared_ptr <ShaderProgram> getShaderProgram();
		void passShaderParamters();
		void addShaderParameter(std::shared_ptr<ShaderParameter> param);
	};
}
#endif // !MATERIAL__H
