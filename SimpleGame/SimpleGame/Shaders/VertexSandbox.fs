#version 330

layout(location=0) out vec4 FragColor;

in float v_Alpha;

uniform float u_Time;

void main()
{
	float newV = 1.0 - v_Alpha;
	newV *= 100.0;
	newV -= u_Time * 20;
	//int lineMask = int(newV)%2;
	float alphaMask = sin(newV);
	FragColor = vec4(1, 1, 1, v_Alpha*alphaMask);
}
