#version 330

in vec3 a_Position;

uniform float u_Time;

const float PI = 3.141592;

out float v_Alpha;

void sinLine()
{
	float newAlpha = 1.0-(a_Position.x + 1.0)/2.0;
	float value = (a_Position.x + 1.0)*PI - u_Time*2;
	float newY = sin(value);
	float d = a_Position.x + 1.0;
	vec4 newPos = vec4(a_Position, 1.0);
	newPos.y = newY*(d*0.2);
	gl_Position = newPos;
	v_Alpha = newAlpha;
}

void main()
{
	sinLine();
}
