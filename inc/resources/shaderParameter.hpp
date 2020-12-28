#include <string>
#include <resources/shader.hpp>
#include <memory>
#include <iostream>

using std::string;
using std::shared_ptr;

namespace Resources
{

	class ShaderParameterBaseClass
	{
		public:
			string name;
			ShaderParameterBaseClass(string name) :name(name) {};
			virtual void setUinform(shared_ptr<ShaderProgram> program)=0;

	};

	template <class T>
	class ShaderParameter :public ShaderParameterBaseClass
	{
		T value;

	public:
		ShaderParameter(string name,T value) : ShaderParameterBaseClass(name), value(value) {};
		void setUinform(shared_ptr<ShaderProgram> program) override
		{
			program->set(name, value);
		}

		void changeParameterValue(T value_) { value = value_; }
		T getParameterValue() { return T; }
	};
}