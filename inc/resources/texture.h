#ifndef TEXTURES__H
#define TEXTURES__H

#include <string>
#include <glad/gl.h>
#include <glm/vec2.hpp>
#include <iostream>
#include <string>

using std::string;

namespace Resources
{
	class Texture {
		GLuint textureID;
		bool generateMipmap;
		glm::ivec2 loadImage(const char* filename);

	public:
		string name;
		Texture(string name, const char* path,bool generate_mipmap);
		~Texture();
		void useTexture(GLuint);
	};

}


#endif // !TEXTURES__H