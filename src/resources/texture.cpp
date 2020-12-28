#include <resources/texture.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace Resources;

glm::ivec2 Texture::loadImage(const char *filename) {
	glm::ivec2 size;
	int channels;
	//Since OpenGL puts the texture origin at the bottom left while images typically has the origin at the top left,
	//We need to till stb to flip images vertically after loading them
	stbi_set_flip_vertically_on_load(true);
	//Load image data and retrieve width, height and number of channels in the image
	//The last argument is the number of channels we want and it can have the following values:
	//- 0: Keep number of channels the same as in the image file
	//- 1: Grayscale only
	//- 2: Grayscale and Alpha
	//- 3: RGB
	//- 4: RGB and Alpha
	//Note: channels (the 4th argument) always returns the original number of channels in the file
	unsigned char* data = stbi_load(filename, &size.x, &size.y, &channels, 4);
	if (data == nullptr) {
		std::cerr << "Failed to load image: " << filename << std::endl;
		return { 0, 0 };
	}
	//Bind the texture such that we upload the image data to its storage
	glBindTexture(GL_TEXTURE_2D, textureID);
	//Set Unpack Alignment to 4-byte (it means that each row takes multiple of 4 bytes in memory)
	//Note: this is not necessary since:
	//- Alignment is 4 by default
	//- Alignment of 1 or 2 will still work correctly but 8 may cause problems
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	//Send data to texture
	//NOTE: the internal format is set to GL_RGBA8 so every pixel contains 4 bytes, one for each channel
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//Generate versions of the texture at smaller level of details (useful for filtering)
	if (generateMipmap) glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data); //Free image data after uploading to GPU
	return size;
}

Texture::Texture(string name, const char* path, bool generate_mipmap):name(name)
{
	//generating texture
	glGenTextures(1, &textureID);

	//loading texture from texture img path
	loadImage(path);
}

void Texture::useTexture(GLuint textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}