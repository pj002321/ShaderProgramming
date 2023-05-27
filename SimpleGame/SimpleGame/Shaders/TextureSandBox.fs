#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_Texcoord;
uniform sampler2D u_TexSampler;
void main()
{
	//FragColor = vec4(v_Texcoord,0,1);
	float x = v_Texcoord.x;
	float y =1.0- abs(v_Texcoord.y * 2.0 -1.0);
	vec2 newTexPos = vec2(x,y);
	
	FragColor = texture(u_TexSampler,newTexPos);
}
