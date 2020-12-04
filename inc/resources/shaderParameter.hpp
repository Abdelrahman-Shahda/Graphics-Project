#include <string>
#include <resources/shader.hpp>
#include <memory>

using std::string;
using std::shared_ptr;

namespace Resources
{
	typedef enum {BASE,FLOAT, MAT4, MAT3, VEC3,VEC4 } ParameterType;

	class ShaderParameter
	{
	protected:
		string name;
		ParameterType type;

	public:
		ShaderParameter(string name) :name(name) { type = BASE; };
		
		virtual void setUinform(shared_ptr<ShaderProgram> program) = 0;
	};

	
	class FloatShaderParamter :public ShaderParameter
	{
		float value;

	public:
		FloatShaderParamter(string name,float value) :ShaderParameter(name) ,value(value) { type = FLOAT; };

		void setParameterValue(float value_)
		{
			value = value_;
		}

		void setUinform(shared_ptr<ShaderProgram> program) override {
			program->set(name, value);
		}
	};
	
	class Matrix4ShaderParamter :public ShaderParameter
	{
		glm::mat4 value;

	public:
		Matrix4ShaderParamter(string name, glm::mat4 value) :ShaderParameter(name), value(value) { type = MAT4; };

		void setParameterValue(glm::mat4 value_)
		{
			value = value_;
		}

		void setUinform(shared_ptr<ShaderProgram> program) override {
			program->set(name, value);
		}
	};


	class Vector3ShaderParamter :public ShaderParameter
	{
		glm::vec3 value;

	public:
		Vector3ShaderParamter(string name, glm::vec3 value) :ShaderParameter(name), value(value) { type = MAT4; };

		void setParameterValue(glm::vec3 value_)
		{
			value = value_;
		}

		void setUinform(shared_ptr<ShaderProgram> program) override {
			program->set(name, value);
		}
	};

	class Vector4ShaderParamter :public ShaderParameter
	{
		glm::vec3 value;

	public:
		Vector4ShaderParamter(string name, glm::vec4 value) :ShaderParameter(name), value(value) { type = VEC4; };

		void setParameterValue(glm::vec4 value_)
		{
			value = value_;
		}

		void setUinform(shared_ptr<ShaderProgram> program) override {
			program->set(name, value);
		}
	};
}
