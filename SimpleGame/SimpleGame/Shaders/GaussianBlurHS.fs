#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_TexPos;

uniform sampler2D u_Texture;
// Weight Info 0~4
uniform float weight[5] = float[] (0.227027,0.1945946,0.1216216,0.054054,0.016216);

void main()
{
	vec2 tex_offset=1.0/textureSize(u_Texture,0); //gets size of single texel (�ػ� Return)
	vec3 result = texture(u_Texture,v_TexPos).rgb*weight[0]; //current fragment's contribution

	// ���� ���ø�
	for(int i=1;i<5;++i) // 8's Sampling
	{
		// ���η� ���ʿ� 4�� + �����ʿ� 4���� �ֺ����� ���ø��ϰ� �� ���� ����Ѵ�.
		// �߽ɿ��� ����ġ�� ���� �۾������� �Ͽ� �迭�� ����ġ���� ����Ͽ� ����ִ´�.
		// �ϳ��� Fragment ����ϱ� ���ؼ� 9���� Sampling�� �ʿ��ϴ�

		result +=texture(u_Texture,v_TexPos + vec2(tex_offset.x*i,0.0)).rgb*weight[i];	// �̵��ϸ鼭 Sampling 
		result +=texture(u_Texture,v_TexPos - vec2(tex_offset.x*i,0.0)).rgb*weight[i];
	}

	FragColor = vec4(result,1.0);
}