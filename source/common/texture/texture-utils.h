#ifndef GRAPHICSPROJECT_TEXTURE_UTILS_H
#define GRAPHICSPROJECT_TEXTURE_UTILS_H

#include <data-types.h>

#include <glad/gl.h>
#include <glm/vec2.hpp>

#include <algorithm>

namespace GraphicsProject::texture_utils {

    // Load an image from a file
    glm::ivec2 loadImage(GLuint texture, const char* filename, bool generate_mipmap = true);
    // Load an image from a file but read it as a grayscale image
    glm::ivec2 loadImageGrayscale(GLuint texture, const char* filename, bool generate_mipmap = true);

    void singleColor(GLuint texture, Color color={255,255,255,255}, glm::ivec2 size={1,1});

    void checkerBoard(GLuint texture, glm::ivec2 size, glm::ivec2 patternSize, GraphicsProject::Color color1, GraphicsProject::Color color2);

}

#endif //GRAPHICSPROJECT_TEXTURE_UTILS_H
