#version 330 core

void main() {
    
	const vec3 positions[6] = vec3[6](
        vec3( -1.0, 1.0, 0.0),
        vec3(1.0,1.0, 0.0),
        vec3( -1.0,-1.0, 0.0),
        vec3(1.0,1.0, 0.0),
        vec3( -1.0,-1.0, 0.0),
        vec3( 1.0, -1.0, 0.0)
    );

    
    gl_Position = vec4(positions[gl_VertexID], 1.0);
}