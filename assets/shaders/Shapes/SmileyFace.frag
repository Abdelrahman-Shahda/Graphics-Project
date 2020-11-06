#version 330 core
out vec4 frag_color;

//uniform vec2 u_resolution;
//uniform vec2 u_mouse;
//uniform float u_time;


void main(){
    vec2 u_resolution =vec2(1280,720);
    vec2 u_mouse= vec2(640,360);
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec2 dist = u_mouse/u_resolution - st.xy;
    dist.x *= u_resolution.x/u_resolution.y;
    float mouse_pct = length(dist);
    vec3 m_color;
    vec2 eye1= (vec2(u_mouse.x-20,u_mouse.y+40)/u_resolution.xy).xy- st.xy;
    vec2 eye2= (vec2(u_mouse.x+20,u_mouse.y+40)/u_resolution.xy).xy- st.xy;
    eye1.x*=u_resolution.x/u_resolution.y;
    eye2.x*=u_resolution.x/u_resolution.y;
    float radeye1=abs(length(eye1));
    float radeye2=abs(length(eye2));


    if(mouse_pct>0.1){
       m_color=vec3(1,1,1);

   }

    else {
       if (mouse_pct>0.05 &&mouse_pct<0.06 && gl_FragCoord.y < u_mouse.y){
           m_color=vec3(1,1,1);
       }
       else if( radeye1<0.015)
       {
           m_color = vec3(1.0, 1.0, 1.0);
       }
       else if( radeye2<0.015)
       {
           m_color = vec3(1.0, 1.0, 1.0);
       }
       else
       m_color=vec3(0,0,0);
   }
    frag_color = vec4(m_color, 1.0);
}