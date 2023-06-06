#version 330

layout(location=0) out vec4 FragColor;

in vec4 v_Color;
in vec2 v_UV;

uniform sampler2D u_Texture;

void circle()
{
	vec2 newValue = v_UV - vec2(0.5, 0.5);
	float d = length(newValue);
	if(d < 0.5f)
	{
		FragColor = v_Color;
	}
	else
	{
		FragColor = vec4(0);
	}
}
void Textured() 
{	
	vec4 result = texture(u_Texture, v_UV)*v_Color;
	FragColor = result;
}
void main()
{
	//FragColor = v_Color;
	//FragColor = vec4(v_UV, 0, 1);
	//circle();
	Textured();
}
