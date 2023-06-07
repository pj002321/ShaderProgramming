#version 330

layout(location=0) out vec4 FragColor;

varying vec4 v_Color;
in vec2 v_UV;

void circle()
{
	vec2 temp = v_UV - vec2(0.5, 0.5);
	float d = length(temp);
	if(d<0.5)
	{
		FragColor = vec4(1)*v_Color;
	}
	else
	{
		FragColor = vec4(0);
	}
}

void circles()
{
	vec2 temp = v_UV - vec2(0.5, 0.5);
	float d = length(temp); 
	float value = sin(30*d);

	FragColor = vec4(value)*v_Color;
}

void main()
{
	//FragColor = v_Color;
	circle();
}
