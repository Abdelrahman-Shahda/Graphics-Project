#ifndef OUR_MeshUtils_H
#define OUR_MeshUtils_H

#include <resources/mesh.hpp>

#include <glm/glm.hpp>

namespace MeshUtils {

    // Load an ".obj" file into the mesh
    bool loadOBJ(Resources::Mesh & mesh, const char* filename);

    void Cuboid(Resources::Mesh & mesh, bool colored_faces = false,
                const glm::vec3& center = {0,0,0},
                const glm::vec3& size = {1,1,1},
                const glm::vec2& texture_offset = {0, 0},
                const glm::vec2& texture_tiling = {1, 1});

    void Sphere(Resources::Mesh& mesh,
                const glm::ivec2& segments = {32, 16},
                bool colored = false,
                const glm::vec3& center = {0,0,0},
                float radius = 0.5f,
                const glm::vec2& texture_offset = {0, 0},
                const glm::vec2& texture_tiling = {1, 1});

    void Plane(Resources::Mesh& mesh,
               const glm::ivec2& resolution = {1, 1},
               bool colored = false,
               const glm::vec3& center={0, 0, 0},
               const glm::vec2& size={1, 1},
               const glm::vec2& texture_offset = {0, 0},
               const glm::vec2& texture_tiling = {1, 1});

}

#endif //OUR_MeshUtils_H
