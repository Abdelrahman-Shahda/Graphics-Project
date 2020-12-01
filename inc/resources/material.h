#ifndef MATERIAL__H
#define MATERIAL__H

#include "shader.hpp"
#include <memory>

namespace Resources {

	class Material
	{
		std::shared_ptr<ShaderProgram> shaderPtr;

	public:
		Material(std::shared_ptr <ShaderProgram> shaderPtr = nullptr);

		//Shader Program
		void setShaderProgram(std::shared_ptr <ShaderProgram> shaderPtr);
		std::shared_ptr <ShaderProgram> getShaderProgram();

		//TODO::shader params
	};
}
#endif // !MATERIAL__H
