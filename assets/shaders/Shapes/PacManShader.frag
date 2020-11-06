#version 330 core
// The first line of any shader must a '#version" command which defines the glsl version to use

// This will be the output (you can choose any name) and it will be sent to the frame buffer (back buffer of the window).
out vec4 frag_color;

uniform vec2 mousePosition;
// This is entry point of the fragment shader and it will be called for every fragment covered by the rasterized geometry
void main() {
    // Here we just output a constant color which is white (R=1, G=1, B=1, A=1)

    //Calculate eyePosition center and Draw it with white color
    vec2 eyePosition = vec2(mousePosition.x, mousePosition.y+60);
    if (abs(length(eyePosition-gl_FragCoord.xy)) <15){
        frag_color = vec4(1.0, 1.0, 1.0, 1.0);

    }
    //Calculate Pac-Man body and draw it with black
    else if(abs(length(mousePosition-gl_FragCoord.xy)) <100){
        //Checking if the point is included between the two lines that represent his mouth
        float y1Intercept = mousePosition.y - mousePosition.x ;
        float y2Intercept = mousePosition.y + mousePosition.x ;
        if((gl_FragCoord.y-gl_FragCoord.x-y1Intercept <=0 &&gl_FragCoord.x >= mousePosition.x && gl_FragCoord.y >= mousePosition.y)||(gl_FragCoord.y+gl_FragCoord.x-y2Intercept >=0 &&gl_FragCoord.x >= mousePosition.x && gl_FragCoord.y <= mousePosition.y)){
            frag_color = vec4(1.0, 1.0, 1.0, 1.0);
        }else{
            frag_color = vec4(0.0,0.0,0.0,0.0);
        }

    }else{
        frag_color = vec4(1.0, 1.0, 1.0, 1.0);
    }
}
