#version 330

layout(location=0) out vec4 FragColor;

uniform sampler2D u_TexSampler;
uniform sampler2D u_MultiTexSampler[2];

uniform vec2 u_XYRepeat;
uniform float u_Step;
uniform float u_SeqNum;

in vec2 v_TexPos;

void P1()
{
	//FragColor = vec4(v_TexPos, 0, 1);
	float x = v_TexPos.x;
	float y = 1.0 - abs(v_TexPos.y * 2.0 - 1.0);
	vec2 newTexPos = vec2(x, y);
	FragColor = texture(u_TexSampler, newTexPos);
}

void P2()
{	
	float x = fract(v_TexPos.x*3.0);
	float dy = v_TexPos.y/3.0; //0~1/3
	float y = floor(3.0*(1.0-v_TexPos.x))/3.0 + dy;
	vec2 newTexPos = vec2(x, y);
	FragColor = texture(u_TexSampler, newTexPos);
	//FragColor = vec4(dy*3);
}

void P3()
{	
	float x = fract(v_TexPos.x*3.0);
	float dy = v_TexPos.y/3.0; //0~1/3
	float y = floor(3.0*v_TexPos.x)/3.0 + dy;
	vec2 newTexPos = vec2(x, y);
	FragColor = texture(u_TexSampler, newTexPos);
	//FragColor = vec4(dy*3);
}

void P4()
{	
	float x = v_TexPos.x;
	float dy = fract(v_TexPos.y*3.0)/3.0; //0~1/3
	float y = floor(3.0*(1.0-v_TexPos.y))/3.0 + dy;
	vec2 newTexPos = vec2(x, y);
	FragColor = texture(u_TexSampler, newTexPos);
	//FragColor = vec4(dy*3);
}

void P5()
{
	float x_repeat = u_XYRepeat.x;
	float y_repeat = u_XYRepeat.y;
	float dx = v_TexPos.x * x_repeat;
	float x = fract(dx + floor((1.0-v_TexPos.y) * y_repeat) * 0.5);
	float y = fract(v_TexPos.y*y_repeat);
	vec2 newTexPos = vec2(x, y);
	FragColor = texture(u_TexSampler, newTexPos);
}

void P6()
{
	float x_repeat = u_XYRepeat.x;
	float y_repeat = u_XYRepeat.y;
	float dy = v_TexPos.y * y_repeat;
	float x = fract(v_TexPos.x*x_repeat);
	float y = fract(dy + floor(v_TexPos.x*x_repeat) * 0.5);
	vec2 newTexPos = vec2(x, y);
	FragColor = texture(u_TexSampler, newTexPos);
}

void P7()
{
	//float x_repeat = u_XYRepeat.x;
	//float y_repeat = u_XYRepeat.y;/
	float y = fract(v_TexPos.x + v_TexPos.y);
	float x = fract(v_TexPos.x + (1.0 - v_TexPos.y));
	vec2 newTexPos = vec2(x, y);
	FragColor = texture(u_TexSampler, newTexPos);
	//FragColor = vec4(x);
}

void MutiTexture()
{
	float x = v_TexPos.x;
	float y = u_Step/6.0 + v_TexPos.y/6.0;
	vec2 newTexPos = vec2(x, y);
	//FragColor = texture(u_MultiTexSampler[int(floor(x))], fract(newTexPos));
	FragColor = texture(u_TexSampler, newTexPos);
}

void SpriteAnim()
{	
	float seqNum =u_SeqNum;
	float nX = float(int(seqNum)%8);
	float nY = floor(seqNum/8.0);
	float x = nX/8.0 + v_TexPos.x/8.0;
	float y = nY/6.0 + v_TexPos.y/6.0;
	vec2 newTexPos = vec2(x, y);
	FragColor = texture(u_TexSampler, newTexPos);
}

void main()
{
	//MutiTexture();
	SpriteAnim();
}
