#ifndef GRAPHICSPROJECT_RENDER_STATE_HPP
#define GRAPHICSPROJECT_RENDER_STATE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <components/component.h>

    // A class that represents render settings
    class RenderState : public Component {
    public:
    bool enable_depth_test = true;
    GLenum depth_function = GL_LEQUAL;
    bool enable_face_culling = true;
    GLenum culled_face = GL_BACK;
    GLenum front_face_winding = GL_CCW;
    bool enable_blending;
    GLenum blend_equation = GL_FUNC_ADD;
    GLenum blend_source_function = GL_SRC_ALPHA, blend_destination_function = GL_ONE_MINUS_SRC_ALPHA;

    glm::vec4 blend_constant_color = {1.0f,1.0f,1.0f,1.0f};
        //Default OpenGL Rendering Settings
        RenderState(std::weak_ptr<Entity> entity) :Component(entity)
	    {
		    type = RENDERSTATE;
        if(enable_depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
        glDepthFunc(depth_function);

        if(enable_face_culling) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
        glCullFace(culled_face);
        glFrontFace(front_face_winding);
        
         if(enable_blending) glEnable(GL_BLEND); else glDisable(GL_BLEND);
        glBlendEquation(blend_equation);
        glBlendFunc(blend_source_function, blend_destination_function);
        glBlendColor(blend_constant_color.r, blend_constant_color.g, blend_constant_color.b, blend_constant_color.a);
        }

        void update()
        {
        if(enable_depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
        glDepthFunc(depth_function);

        if(enable_face_culling) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
        glCullFace(culled_face);
        glFrontFace(front_face_winding);
        
         if(enable_blending) glEnable(GL_BLEND); else glDisable(GL_BLEND);
        glBlendEquation(blend_equation);
        glBlendFunc(blend_source_function, blend_destination_function);
        glBlendColor(blend_constant_color.r, blend_constant_color.g, blend_constant_color.b, blend_constant_color.a);
        }


    };

#endif //GRAPHICSPROJECT_RENDERSTATE_HPP
