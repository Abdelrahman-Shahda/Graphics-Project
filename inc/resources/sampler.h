//
// Created by shaimaa on 12/29/2020.
//
#include<glad/gl.h>
#include <resources/texture.h>

#ifndef GRAPHICSPROJECT_SAMPLER_H
#define GRAPHICSPROJECT_SAMPLER_H

#endif //GRAPHICSPROJECT_SAMPLER_H
namespace Resources {
    class sampler {
        GLuint sampler_;
        // GL_REPEAT OR GL_MIRRORED_REPEAT OR GL_CLAMP_TO_EDGE OR GL_CLAMP_TO_BORDER
        int wrab_s;
        int wrab_t;
        int magnification_filter;
        int minification_filter;
        int GL_texture_mag;
        int GL_texture_min;
        int GL_texture_wrap_s;
        int GL_texture_wrap_t;
        GLfloat max_anisotropy_upper_bound ;


    public:

        sampler();
        sampler(const sampler &sampler1);
        void usesampler();
        GLuint getsamplerobject() const;
        void set(int wrab_s_, int wrab_t_,int magnification_filter_,int minification_filter_,int gl_texture_mag, int gl_texture_min,int gl_texture_wrap_s,int gl_texture_wrap_t,GLfloat max_anisotropy_upper_bound_=1.0f);
        ~sampler();
    };
}