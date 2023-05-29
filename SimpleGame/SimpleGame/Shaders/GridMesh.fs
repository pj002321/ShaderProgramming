#version 330

out vec4 FragColor;
in float v_greyScale;
in vec2 v_TexPos;


uniform sampler2D u_Texture;



void main()
{
    vec2 newTexPos = fract(v_TexPos*2.0);
    FragColor = v_greyScale*texture(u_Texture,v_TexPos);
}
