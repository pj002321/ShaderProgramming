#version 330

layout(location=0) out vec4 FragColor;

uniform sampler2D u_TexSampler;
uniform sampler2D u_MultiTexSampler[2];
uniform float u_seqNum;

uniform vec2 u_XYRepeat;

in vec2 v_Texcoord;
void P4()
{
	float x = v_Texcoord.x;
	float y =1.0- abs(v_Texcoord.y * 2.0 -1.0);
	vec2 newTexPos = vec2(x,y);
	
	FragColor = texture(u_TexSampler,newTexPos);
}
void P5()
{
	float x_repeat=u_XYRepeat.x;
	float y_repeat=u_XYRepeat.y;
	float dx = v_Texcoord.x*x_repeat;
	float x =fract(dx + floor((1.0-v_Texcoord.y) * y_repeat) * 0.5);
	float y =fract(v_Texcoord.y * y_repeat);
	vec2 newTexPos = vec2(x,y);
	FragColor = texture(u_TexSampler,newTexPos);
}
void P6()
{
	float x_repeat=u_XYRepeat.x;
	float y_repeat=u_XYRepeat.y;
	float dy = v_Texcoord.y*y_repeat;
	float x = fract(v_Texcoord.x* x_repeat);
	float y = fract(dy + floor((1.0-v_Texcoord.x )*x_repeat) * 0.5);
	vec2 newTexPos = vec2(x,y);
	FragColor = texture(u_TexSampler,newTexPos);
}

// Test - 해결 완료
void P7()
{
//	float x_repeat=u_XYRepeat.x;
//	float y_repeat=u_XYRepeat.y;
	float y = fract(v_Texcoord.y+v_Texcoord.x)-0.25;
	float x = fract(v_Texcoord.x+(1.0-v_Texcoord.y))+0.25;
	
	vec2 newTexPos = vec2(x,y);
	FragColor = texture(u_TexSampler,newTexPos);
}

void MultiTexture()
{
	FragColor = texture(u_TexSampler, v_Texcoord);
}
void SpriteAnim() 
{
	float seqNym = u_seqNum;
	float nX =float(int(seqNym)%8);
	float nY =floor(seqNym/8.0);
	float x = nX/8.0+v_Texcoord.x/8.0;	
	float y = nY/6.0+v_Texcoord.y/6.0;
	vec2 newTexPos = vec2(x,y);
	FragColor = texture(u_TexSampler, newTexPos);
}
void main()
{
	//FragColor = vec4(v_Texcoord,0,1);

	SpriteAnim();
}
