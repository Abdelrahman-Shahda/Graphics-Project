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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // This parameter defines the minification filter. This filter will be used when the texture is minified (1 screen pixel covers more than 1 texture pixel).
    // The possible values are:
    //  -   Similar to magnification, we have 2 modes that ignores the mip maps:
    //      -   GL_NEAREST which returns the color from the nearest texture pixel.
    //      -   GL_LINEAR which linearly interpolates the colors of the 4 surrounding pixels.
    //  -   Specific to minification, we have 4 modes that follow the form GL_*_MIPMAP_*
    //      where the 1st wild card specifies the filtering within a texture and the 2nd wild card specifies the filtering between mip levels.
    //      -   GL_NEAREST_MIPMAP_NEAREST which returns the color of the nearest pixel in the nearest mip level.
    //      -   GL_NEAREST_MIPMAP_LINEAR which linearly interpolates between the colors of the nearest pixel in each of the surrounding mip levels.
    //      -   GL_LINEAR_MIPMAP_NEAREST which applies linear-filtering in the nearest mip level.
    //      -   GL_LINEAR_MIPMAP_LINEAR which linearly interpolates the results of the linear filtering in each of the surrounding mip levels.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // These pair of parameters define the Wrap mode along the 2 texture coordinates: S and T.
    // The Wrap mode specifies how to deal with texture coordinates that lie outside the range [0, 1].
    // The possible values are:
    //  -   GL_REPEAT: this mode keeps adding or subtracting 1 from the coordinate till it return to the range [0, 1]. This leads to a texture repeating effect since for example, the coordinates -0.2, 0.8, 1.8, 2.8, and so on all maps to same location in the texture.
    //  -   GL_MIRRORED_REPEAT: similar to GL_REPEAT but each repetition is the mirrored version of the ones surrounding it.
    //  -   GL_CLAMP_TO_BORDER: this mode returns the border color for coordinates that exceed the range.
    //  -   GL_CLAMP_TO_EDGE: this modes clamps the textures coordinates to the range [0, 1] before sampling. So any value below 0 will be 0 and any value above 1 will be 1.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // This parameter identifies the border color to be used with the wrap mode GL_CLAMP_TO_BORDER
    glm::vec4 border_color = {1,1,1,1};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(border_color));
    // This parameter identifies the maximum anisotropy which can be used to enable and specify the quality of the anisotropic filtering.
    // Minimum value is 1.0 which is equivalent to disabling the anisotropic filtering.
    // Maximum value depends on the GPU and can be enumerated using the glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy_upper_bound);
    // Anisotropic filtering allows the use of mip maps on samples where the derivatives vary vastly on the X & Y directions of the screen space without over-blurring the result.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0f);
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