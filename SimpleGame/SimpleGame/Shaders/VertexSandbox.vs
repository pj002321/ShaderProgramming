#version 330

in vec3 a_Position; //ATTRIBUTE (VS INPUT)

const float PI = 3.141592;

uniform float u_Time;

out float v_Alpha;

void main()
{
	float value = PI*(a_Position.x + 1.0); 
	float d = a_Position.x + 1.f;
	float newY = 0.2*d*sin(value - u_Time);
	vec4 newPos = vec4(a_Position, 1.0);
	newPos.y = newY;
	gl_Position = newPos;

	v_Alpha = 1.0 - (a_Position.x + 1.0)/2.0;
}
