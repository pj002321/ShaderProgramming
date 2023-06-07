#version 330

in vec3 a_Position; //ATTRIBUTE (VS INPUT)
in vec3 a_Vel;
in float a_EmitTime;
in float a_LifeTime;
in float a_Period;
in float a_Amp;
in float a_Value;
in vec4 a_Color;
in vec2 a_UV;

uniform float u_Time;

const vec3 c_Gravity = vec3(0.0, -1.8, 0.0);
const float c_lifeTime = 2.0;
const vec3 c_Vel = vec3(0.0, -0.8, 0.0);
const float c_PI = 3.141592;
const float c_Period = 1.0;
const float c_Amp = 1.0;

varying vec4 v_Color;
out vec2 v_UV;

void GraphSin()
{
	float t = u_Time - a_EmitTime;
	vec4 newPosition = vec4(0, 0, 0, 1);
	float newAlpha = 0.0;
	
	if(t < 0.0)
	{

	}
	else
	{
		/*float R = 7.0;
		float r = 4.0;
		float d = 1.0;
		float theta = a_Value * 2.0 * c_PI;
		float nX = (R-r)*cos(theta) + d * cos((R-r)*theta/r);
		float nY = (R-r)*sin(theta) - d * sin((R-r)*theta/r);*/

		float newT = a_LifeTime * fract(t/a_LifeTime);
		float nX = sin(a_Value * 2.0 * c_PI);
		float nY = cos(a_Value * 2.0 * c_PI);
		newPosition.x = a_Position.x + nX + newT*a_Vel.x;
		newPosition.y = a_Position.y + nY + newT*a_Vel.y;
		
		vec2 newDir = vec2(-a_Vel.y, a_Vel.x);
		newDir = normalize(newDir);
		newPosition.xy += newT*a_Amp*sin(a_Period * newT * 2.0 * c_PI) * 
							newDir;

		newAlpha = 1.0 - newT/a_LifeTime;
		newAlpha = pow(newAlpha, 2);
	}	
	gl_Position = newPosition;
	v_Color = vec4(a_Color.rgb, a_Color.a*newAlpha);
	v_UV = a_UV;
}

void P1()
{
	float t = u_Time - a_EmitTime;
	vec4 newPosition = vec4(0, 0, 0, 1);

	if(t < 0.0)
	{

	}
	else
	{
		float newT = a_LifeTime * fract(t/a_LifeTime);
		newPosition.xyz = a_Position 
							+ a_Vel*newT
							+ 0.5 * c_Gravity * newT * newT;
		newPosition.w = 1;
	}
	gl_Position = newPosition;
	v_Color = a_Color;
	v_UV = a_UV;
}

void main()
{
	GraphSin();
	//P1();
}