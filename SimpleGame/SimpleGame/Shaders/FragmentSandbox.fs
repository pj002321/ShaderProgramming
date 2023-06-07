#version 330

layout(location=0) out vec4 FragColor0; //GL_COLOR_ATTACHMENT0 
layout(location=1) out vec4 FragColor1; //GL_COLOR_ATTACHMENT1
layout(location=2) out vec4 FragColor2; //GL_COLOR_ATTACHMENT2
layout(location=3) out vec4 FragColor3; //GL_COLOR_ATTACHMENT3
layout(location=4) out vec4 FragColor4; //GL_COLOR_ATTACHMENT4

in vec2 v_Texcoord;

uniform vec2 u_Point;
uniform vec2 u_Points[3];
uniform float u_Time;
const float c_PI = 3.141592;

uniform sampler2D u_Texture;

void test()
{
	float newValueX = v_Texcoord.x * 10.0 * c_PI;
	float newValueY = v_Texcoord.y * 10.0 * c_PI;
	float outColorGreyVertical = sin(newValueX);
	float outColorGreyHorizontal = sin(newValueY);
	float newColor = max(outColorGreyVertical, outColorGreyHorizontal);
	FragColor0 = vec4(newColor);
}

void circle()
{
	vec2 temp = v_Texcoord - u_Points[0];
	float d = length(temp);
	vec2 temp1 = v_Texcoord - u_Points[1];
	float d1 = length(temp1);
	if(d<0.1 || d1<0.1)
	{
		FragColor1 = vec4(1);
	}
	else
	{
		FragColor1 = vec4(0);
	}
}

void circles()
{
	vec2 temp = v_Texcoord - u_Points[0];
	float d = length(temp); 
	float value = sin(30*d);

	FragColor0 = vec4(value);
}

void radar()
{
	vec2 temp = v_Texcoord - vec2(0.5, 1.0);
	float d = length(temp); 
	float value = 0.2*(pow(sin(d*2*c_PI - 50*u_Time), 12)-0.5);
	float temp1 = ceil(value);

	vec4 result = vec4(0);
	for(int i=0; i<3; i++)
	{
		vec2 temp = v_Texcoord - u_Points[i];
		float d = length(temp);

		if(d<0.03)
		{
			result += 1.0*temp1;
		}
	}
	


	FragColor2 = vec4(result + 10*value);
}

void flag()
{
	float finalColor = 0;
	for(int i=0; i<10; i++)
	{
		float newTime = u_Time + i*0.2;
		float newColor = v_Texcoord.x*0.5*
				sin(v_Texcoord.x*c_PI*2 - 10*newTime);
		float sinValue = sin(v_Texcoord.x*c_PI*2*10 - 500*newTime);
		float width = 0.01*v_Texcoord.x*5+0.001;
		if(2.0*(v_Texcoord.y-0.5) > newColor && 
		   2.0*(v_Texcoord.y-0.5) < newColor + width)
		{
			finalColor += 1*sinValue*(1.0-v_Texcoord.x);
		}
		else
		{
		}
	}
	FragColor3 = vec4(finalColor);
}

void realFlag()
{
	float period = (v_Texcoord.x + 1.0) * 1.0;
	float xValue = v_Texcoord.x*2.0*c_PI*period;
	float yValue = ((1.0-v_Texcoord.y)-0.5)*2.0;
	float sinValue = 0.25*sin(xValue-100.0*u_Time);
	if(sinValue*v_Texcoord.x + 0.75 > yValue 
	&& 
	   sinValue*v_Texcoord.x - 0.75 < yValue)
	{
		float vX = v_Texcoord.x;
		float yWidth = 1.5;
		float yDistance = yValue - (sinValue*v_Texcoord.x - 0.75);
		float vY = 1.0-yDistance/yWidth;
		FragColor4 = texture(u_Texture, vec2(vX, vY));
		//FragColor = vec4(vX, vY, 0, 1);
	}
	else
	{
		FragColor4 = vec4(0);
	}
}
void main()
{
	test();
	circle();
	//circles();
	radar();
	flag();
	realFlag();
}
