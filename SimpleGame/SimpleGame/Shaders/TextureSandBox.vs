#version 330

in vec3 a_Position;
in vec2 a_Texcoord;

out vec2 v_Texcoord;



void main()
{
	vec4 newPosition=vec4(a_Position,1.0);

	gl_Position = newPosition;

	v_Texcoord=a_Texcoord;
}
