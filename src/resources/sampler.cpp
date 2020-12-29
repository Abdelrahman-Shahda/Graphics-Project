//
// Created by shaimaa on 12/29/2020.
//
#include <resources/sampler.h>
using namespace Resources;
sampler::sampler() {
    glGenSamplers(1,&sampler_);
}

void sampler::usesampler() {
    glGenSamplers(1, &sampler_);
    glSamplerParameteri(sampler_, GL_texture_mag, magnification_filter);
    glSamplerParameteri(sampler_, GL_texture_min, minification_filter);
    glSamplerParameteri(sampler_, GL_texture_wrap_s, wrab_s);
    glSamplerParameteri(sampler_, GL_texture_wrap_t, wrab_t);
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy_upper_bound);
    glSamplerParameterf(sampler_, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy_upper_bound);
    for(GLuint unit = 0; unit < 5; ++unit) glBindSampler(unit, sampler_);

}

void sampler::set(int wrab_s_, int wrab_t_,int magnification_filter_,int minification_filter_,int gl_texture_mag, int gl_texture_min,int gl_texture_wrap_s,int gl_texture_wrap_t,GLfloat max_anisotropy_upper_bound_){
    wrab_s=wrab_s_;
    wrab_t=wrab_t_;
    magnification_filter=magnification_filter_;
    minification_filter=minification_filter_;
    GL_texture_mag=gl_texture_mag;
    GL_texture_min=gl_texture_min;
    GL_texture_wrap_s=gl_texture_wrap_s;
    GL_texture_wrap_t=gl_texture_wrap_t;
    max_anisotropy_upper_bound=max_anisotropy_upper_bound_;
}
GLuint sampler::getsamplerobject() const {
    return sampler_;
}
 sampler::sampler(const sampler &sampler1) {
     sampler_=sampler1.getsamplerobject();
 }
 sampler::~sampler() {
         glDeleteSamplers(1,&sampler_);
     }