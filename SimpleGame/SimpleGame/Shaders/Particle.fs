#version 330

layout(location=0) out vec4 FragColor;
layout(location=1) out vec4 FragColorHigh;

varying vec4 v_Color;
in vec2 v_UV;

uniform sampler2D u_Texture;

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
void Textured()
{
	vec4 result = texture(u_Texture,v_UV)*v_Color;
	float brightness = dot( result.rgb,vec3(0.2126,0.7152,0.0722) );
	FragColor = result;

	if(brightness>1.0)
		FragColorHigh=result;
	else
		FragColorHigh=vec4(0);

}
void main()
{
	//FragColor = v_Color;
	//circle();
	Textured();
}
