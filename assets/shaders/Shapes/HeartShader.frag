#version 330 core
out vec4 frag_color;
uniform vec2 mousePosition;

//Heart shape consists of an equilateral triangle and two semi circle
//Length of side of triangle =500 pixels
//Radius of each semi circle =125 pixels
const float sideLength=500;
const float radius=125;

void main() {
	//Center of shape is tangency point between 2 circles 
	//Every other point is calculated from this center
	vec2 HeartCenter=mousePosition;

	//triangle vertices
	vec2 triBasePoint=vec2(HeartCenter.x,HeartCenter.y-433);
	vec2 rightV=HeartCenter-vec2(radius*2+3,-10);
	vec2 leftV=HeartCenter+vec2(radius*2+3,10);

	//Semi circles centers
	vec2 centerCircle1=HeartCenter-vec2(radius,0);
	vec2 centerCircle2=HeartCenter+vec2(radius,0);

	frag_color=vec4(1.0,1.0,1.0,1.0);

	if(distance(gl_FragCoord.xy,centerCircle1) <= radius && gl_FragCoord.y>=centerCircle1.y)
	{
		frag_color=vec4(1.0,0.0,0.0,1.0);
		return;
	}
	
	else if(distance(gl_FragCoord.xy,centerCircle2) <= radius && gl_FragCoord.y>=centerCircle2.y)
	{
		frag_color=vec4(1.0,0.0,0.0,1.0);
		return;
	}

	//checking if point is inside triangle
	float a1=triBasePoint.y - rightV.y;
	float b1=triBasePoint.x - rightV.x;
	float c1=a1*triBasePoint.x - b1*triBasePoint.y;

	float a2=triBasePoint.y - leftV.y;
	float b2=triBasePoint.x - leftV.x;
	float c2=a2*triBasePoint.x - b2*triBasePoint.y;

	float d1=gl_FragCoord.y*b1 - gl_FragCoord.x*a1 +c1;
	float d2=gl_FragCoord.y*b2 - gl_FragCoord.x*a2 +c2;

	if(d1>0 && d2<0 && gl_FragCoord.y<= HeartCenter.y)
		frag_color=vec4(1.0,0.0,0.0,1.0);
}