#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_TexPos;

uniform sampler2D u_TextureScene;
uniform sampler2D u_TextureBloom;
uniform float u_Exposure;

void main()
{
	const float gamma =2.2;
	vec3 hdrColor = texture(u_TextureScene,v_TexPos).rgb;
	vec3 bloomColor = texture(u_TextureBloom,v_TexPos).rgb;
	hdrColor+=bloomColor;

	//tone mapping : Reinhard tone mapping
	vec3 result = vec3(1.0) - exp(-hdrColor * u_Exposure);

	result = pow(result,vec3(1.0/gamma));
	FragColor = vec4(result,1.0);
}
