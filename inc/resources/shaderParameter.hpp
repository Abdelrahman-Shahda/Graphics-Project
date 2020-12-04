#include <string>
#include <resources/shader.hpp>


namespace Resources
{
	typedef enum {BASE,FLOAT, MAT4, MAT3, VEC3,VEC4 } PARAMATER_TYPE;

	template  <class T>
	class ShaderParameter
	{
	protected:
		T value;
		std::string name;
		ParameterType type;
		void setValue(T value_) { this->value = value_; };

	public:
		ShaderParameter(PARAMATER_TYPE paramaterType,string name) :type(paramaterType), name(name) {};
		void setUinform(T value,ShaderProgram program){
			this->setValue(value);
			program.set(name, value);
		}
	};

	//TODO:: check if this class is necessary
	//check if it's necessary
	//Instantiating fload parameter from shader Class
	class FloatShaderParamter :public ShaderParameter<float>
	{
		FloatShaderParamter() :ShaderParameter<float>(FLOAT) {};
		 void setUinform(float value, ShaderProgram program) override
		{
			 this->setValue(value);
			 program.set(name, value);
		}
	};
	
}
