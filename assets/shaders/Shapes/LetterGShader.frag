#version 330 core
// The first line of any shader must a '#version" command which defines the glsl version to use

// This will be the output (you can choose any name) and it will be sent to the frame buffer (back buffer of the window).
out vec4 frag_color;
uniform vec2 mousePosition;

// This is entry point of the fragment shader and it will be called for every fragment covered by the rasterized geometry
void main() {
    // Here we just output a constant color which is white (R=1, G=1, B=1, A=1)
    //Calculate Circle Frame center and Draw it
     //Draw a Circle Frame
    if (abs(length(vec4(mousePosition.x,mousePosition.y,0.0,0.0)-gl_FragCoord)) <150 && abs(length(vec4(mousePosition.x,mousePosition.y,0.0,0.0)-gl_FragCoord)) >100 && gl_FragCoord.x < (mousePosition.x+100))
    {
        //Draw a Trianlge + Rectangle in White to erase part of the frame
        if((gl_FragCoord.x>(mousePosition.x+60) && gl_FragCoord.x<(mousePosition.x+100) && gl_FragCoord.y<(mousePosition.y+110) && gl_FragCoord.y>(mousePosition.y+80) && (4*gl_FragCoord.y < (3*gl_FragCoord.x + (4*mousePosition.y+320-180-3*mousePosition.x)) ) ) || (gl_FragCoord.x>(mousePosition.x+60) && gl_FragCoord.x<(mousePosition.x+160) && gl_FragCoord.y>(mousePosition.y-20) && gl_FragCoord.y<(mousePosition.y+80) ) )
        frag_color = vec4(1.0, 1.0, 1.0, 1.0);
        else
        frag_color = vec4(0.0, 0.0, 0.0, 1.0);

    }
        else
    {
        frag_color = vec4(1.0, 1.0, 1.0, 1.0);

    }
    //Draw Vertical Rectangle
     if (abs((mousePosition.x+75)-gl_FragCoord.x) < 25 && gl_FragCoord.y > (mousePosition.y-100) && gl_FragCoord.y < (mousePosition.y-20) )
    {
        frag_color = vec4(0.0, 0.0, 0.0, 1.0);
    }




}
