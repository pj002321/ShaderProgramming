#version 330

in vec3 a_Position; //ATTRIBUTE (VS INPUT)
in vec3 a_Position1; //ATTRIBUTE (VS INPUT)
in vec4 a_Color;

uniform vec4 u_Trans;

uniform float u_Scale;

out vec4 v_Color;

void main()
{
	vec4 newPosition;
	newPosition.xy = u_Scale * (a_Position.xy+a_Position1.xy)
						* u_Trans.w + u_Trans.xy;
	newPosition.z = 0;
	newPosition.w= 1;
	gl_Position = newPosition;
	v_Color = a_Color;
}
