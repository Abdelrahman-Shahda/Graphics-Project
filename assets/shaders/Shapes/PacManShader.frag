#version 330 core
// The first line of any shader must a '#version" command which defines the glsl version to use

// This will be the output (you can choose any name) and it will be sent to the frame buffer (back buffer of the window).
out vec4 frag_color;

// This is entry point of the fragment shader and it will be called for every fragment covered by the rasterized geometry
void main() {
    // Here we just output a constant color which is white (R=1, G=1, B=1, A=1)

    if (abs(length(vec4(640,420,0.0,0.0)-gl_FragCoord)) <15){
        frag_color = vec4(1.0, 1.0, 1.0, 1.0);

    }
    else if(abs(length(vec4(640,360,0.0,0.0)-gl_FragCoord)) <100){
        if((gl_FragCoord.y-gl_FragCoord.x+280 <=0 &&gl_FragCoord.x >= 640 && gl_FragCoord.y >= 360)||(gl_FragCoord.y+gl_FragCoord.x-1000 >=0 &&gl_FragCoord.x >= 640 && gl_FragCoord.y <= 360)){
            frag_color = vec4(1.0, 1.0, 1.0, 1.0);
        }else{
            frag_color = vec4(0.0,0.0,0.0,0.0);
        }

    }else{
        frag_color = vec4(1.0, 1.0, 1.0, 1.0);

    }
}
