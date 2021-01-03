//
// Created by shaimaa on 12/29/2020.
//
#include<glad/gl.h>
#include <resources/texture.h>

#ifndef GRAPHICSPROJECT_SAMPLER_H
#define GRAPHICSPROJECT_SAMPLER_H


namespace Resources {
    class Sampler {
        GLuint sampler;
        // GL_REPEAT OR GL_MIRRORED_REPEAT OR GL_CLAMP_TO_EDGE OR GL_CLAMP_TO_BORDER
        int wrabS;
        int wrabT;
        int magnificationFilter;
        int minificationFilter;
        GLfloat anistropy;
		GLfloat maxAnistropoy;
		glm::vec4 borderColor;

		void passSamplerParams();

    public:
        Sampler(int wrab_s_ = GL_REPEAT, int wrab_t_ = GL_REPEAT, int magnification_filter_ = GL_LINEAR, int minification_filter_ = GL_LINEAR_MIPMAP_LINEAR, glm::vec4 border_color = { 1,1,1,1 }, GLfloat max_anisotropy_upper_bound_ = 1.0f);
        void useSampler(GLuint textureUnit);
        GLuint getSamplerobject() const;
        void setSamplerParams(int wrab_s_, int wrab_t_ ,int magnification_filter_,int minification_filter_, glm::vec4 border_color,GLfloat anistropy_);
        ~Sampler();

		Sampler(Sampler const &) = delete;
		Sampler &operator=(Sampler const &) = delete;
		operator GLuint() const; 
    };
}

#endif //GRAPHICSPROJECT_SAMPLER_H