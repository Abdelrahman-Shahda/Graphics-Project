//
// Created by shaimaa on 12/29/2020.
//
#include <resources/sampler.h>
using namespace Resources;

Sampler::Sampler(int wrab_s_, int wrab_t_, int magnification_filter_, int minification_filter_, glm::vec4 border_color, GLfloat anistropy_)
{
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnistropoy);
	glGenSamplers(1,&sampler);
	setSamplerParams(wrab_s_, wrab_t_, magnification_filter_, minification_filter_, border_color, anistropy_);
}

void Sampler::passSamplerParams()
{
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, magnificationFilter);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, minificationFilter);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, wrabS);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, wrabT);
	glSamplerParameterfv(sampler, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(borderColor));
	glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, anistropy);
}


void Sampler::useSampler(GLuint textureUnit) {
    glBindSampler(textureUnit, sampler);
}

void Sampler::setSamplerParams(int wrab_s_, int wrab_t_, int magnification_filter_, int minification_filter_, glm::vec4 border_color, GLfloat anistropy_)
{
    wrabS=wrab_s_;
    wrabT=wrab_t_;
    magnificationFilter=magnification_filter_;
    minificationFilter=minification_filter_;
	anistropy = anistropy_ > maxAnistropoy ? maxAnistropoy : anistropy_;
	borderColor = border_color;
	passSamplerParams();
}

GLuint Sampler::getSamplerobject() const {
    return sampler;
}

 Sampler::~Sampler() {
         glDeleteSamplers(1,&sampler);
     }

 Sampler::operator GLuint() const { return sampler; }
