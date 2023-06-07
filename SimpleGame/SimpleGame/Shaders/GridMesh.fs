#version 330

layout(location=0) out vec4 FragColor;

in float v_greyScale;
in vec2 v_TexPos;

uniform sampler2D u_Texture;
uniform float u_Time;

const float c_PI = 3.141592;

void realFlag()
{
	float period = (v_TexPos.x + 1.0) * 1.0;
	float xValue = v_TexPos.x*2.0*c_PI*period;
	float yValue = ((1.0-v_TexPos.y)-0.5)*2.0;
	float sinValue = 0.25*sin(xValue-1.0*u_Time);
	if(sinValue*v_TexPos.x + 0.75 > yValue 
	&& 
	   sinValue*v_TexPos.x - 0.75 < yValue)
	{
		float vX = v_TexPos.x;
		float yWidth = 1.5;
		float yDistance = yValue - (sinValue*v_TexPos.x - 0.75);
		float vY = 1.0-yDistance/yWidth;
		FragColor = texture(u_Texture, vec2(vX, vY));
		//FragColor = vec4(vX, vY, 0, 1);
	}
	else
	{
		FragColor = vec4(0);
	}
}

void main()
{
	vec2 newTexPos = fract(v_TexPos * 2.0);
	//FragColor = v_greyScale * vec4(v_TexPos, 0, 1);
	FragColor = v_greyScale * texture(u_Texture, newTexPos);
	//realFlag();
}
