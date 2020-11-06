#version 330 core
// The first line of any shader must a '#version" command which defines the glsl version to use

// This will be the output (you can choose any name) and it will be sent to the frame buffer (back buffer of the window).
out vec4 frag_color;

// This is entry point of the fragment shader and it will be called for every fragment covered by the rasterized geometry
void main() {
    // Here we just output a constant color which is white (R=1, G=1, B=1, A=1)

     //Draw a Circle Frame
    if (abs(length(vec4(640,420,0.0,0.0)-gl_FragCoord)) <150 && abs(length(vec4(640,420,0.0,0.0)-gl_FragCoord)) >100 && gl_FragCoord.x < 740)
    {
        //Draw a Trianlge + Rectangle in White to erase part of the frame
        if((gl_FragCoord.x>700 && gl_FragCoord.x<740 && gl_FragCoord.y<530 && gl_FragCoord.y>500 && (4*gl_FragCoord.y < (3*gl_FragCoord.x - 100) ) ) || (gl_FragCoord.x>700 && gl_FragCoord.x<800 && gl_FragCoord.y>400 && gl_FragCoord.y<500 ) )
        frag_color = vec4(1.0, 1.0, 1.0, 1.0);
        else
        frag_color = vec4(0.0, 0.0, 0.0, 1.0);

    }
        else
    {
        frag_color = vec4(1.0, 1.0, 1.0, 1.0);

    }
    //Draw Vertical Rectangle
     if (abs(715-gl_FragCoord.x) < 25 && gl_FragCoord.y > 320 && gl_FragCoord.y < 400 )
    {
        frag_color = vec4(0.0, 0.0, 0.0, 1.0);
    }




}
