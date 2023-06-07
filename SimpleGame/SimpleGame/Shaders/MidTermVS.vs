#version 330

in vec3 a_Position; 
in vec2 a_TexPos;
in float a_Value;
uniform float u_Time;
const float PI = 3.141592;

out vec2 v_TexPos;

void P29()
{
	float x = a_Position.x + sin(u_Time);
	float y = a_Position.y + cos(u_Time);
	vec4 newPosition = vec4(x, y, 0.0, 1.0);
	gl_Position = newPosition;
	v_TexPos = a_TexPos;
}

void P31()
{
	float x = a_Position.x + 2.0*fract(u_Time)-1.0;
	float y = a_Position.y + sin(u_Time*2.0*PI);
	vec4 newPosition = vec4(x, y, 0.0, 1.0);
	gl_Position = newPosition;
	v_TexPos = a_TexPos;
}

void P33()
{
	float x = a_Position.x + 2.0*fract(u_Time)-1.0;
	float y = a_Position.y + sin(a_Value*u_Time*2.0*PI);
	vec4 newPosition = vec4(x, y, 0.0, 1.0);
	gl_Position = newPosition;
	v_TexPos = a_TexPos;
}

void P35()
{
	float sign = 2.0*(a_Value-1.5);
	float x = a_Position.x - sign*2.0*fract(u_Time)+sign;
	float y = a_Position.y + sin(u_Time*2.0*PI);
	vec4 newPosition = vec4(x, y, 0.0, 1.0);
	gl_Position = newPosition;
	v_TexPos = a_TexPos;
}

void main()
{
	float sign = 2*(a_Value - 1.5);
	float x = a_Position.x - sign*2*fract(u_Time)+sign;
	float y = a_Position.y + sin(u_Time*2.0*PI);
	vec4 newPosition = vec4(x, y, 0.0, 1.0);
	gl_Position = newPosition;
	v_TexPos = a_TexPos;
}
