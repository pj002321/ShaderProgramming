#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_TexPos;

uniform sampler2D u_Texture;
// Weight Info 0~4
uniform float weight[5] = float[] (0.227027,0.1945946,0.1216216,0.054054,0.016216);

void main()
{
	vec2 tex_offset=1.0/textureSize(u_Texture,0); //gets size of single texel (해상도 Return)
	vec3 result = texture(u_Texture,v_TexPos).rgb*weight[0]; //current fragment's contribution

	// 수평 샘플링
	for(int i=1;i<5;++i) // 8's Sampling
	{
		// 가로로 왼쪽에 4개 + 오른쪽에 4개를 주변에서 샘플링하고 그 합을 출력한다.
		// 중심에서 가중치가 점점 작아지도록 하여 배열에 가중치들을 계산하여 집어넣는다.
		// 하나의 Fragment 출력하기 위해서 9개의 Sampling이 필요하다

		result +=texture(u_Texture,v_TexPos + vec2(tex_offset.x*i,0.0)).rgb*weight[i];	// 이동하면서 Sampling 
		result +=texture(u_Texture,v_TexPos - vec2(tex_offset.x*i,0.0)).rgb*weight[i];
	}

	FragColor = vec4(result,1.0);
}
