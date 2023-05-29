#version 330

layout(location=0) out vec4 FragColor;

in float v_Alpha;

uniform float u_Time;

void main()
{
	float newV = 1.0 - v_Alpha; //증가하도록
	newV *= 100.0; //0~30
	newV -= u_Time * 3 ;
	//int lineMask = int(newV) % 2;
	float alphaMask = sin(newV);
   FragColor = vec4(1,1,1, alphaMask);
}