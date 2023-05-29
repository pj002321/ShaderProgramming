#version 330

in vec3 a_Position;
out float v_greyScale;
out vec2 v_TexPos;

const float PI = 3.141592;

uniform float u_Time;

/*
void  realFlag()
{
    float period = (v_TexPos.x +1.0);
    float xValue = v_TexPos.x*2.0*PI*period;
    float yValue = ((1.0-v_TexPos.y)-0.5)*2.0;
    float sinvalue = 0.25*sin(xValue-1.0*u_Time);
    if(sinvalue*v_TexPos.x+0.75)
    {
    }
}
*/
void main()
{
    float x = a_Position.x;
    float value = (a_Position.x+0.5)*2.0*PI-u_Time;
    float temp = x + 0.5;
    float y = a_Position.y+0.5*sin(value)*temp;

    vec4 newPosition = vec4(x,y,0.0, 1.0);
    vec3 targetPos = vec3(1.0,-1.0,0.0);

    float timeY= length(a_Position.xy-targetPos.xy);
    //(a_Position.y + 0.5);
    float newTime = u_Time - timeY * 3.0;
    newTime = max(0, newTime);


    vec3 morphPos = mix(newPosition.xyz, targetPos, newTime);

    gl_Position = vec4(morphPos,1);
    v_greyScale = 0.3+(sin(value)+1.0)/2.0;

    float tx = a_Position.x+0.5;
    float ty = 1.0-a_Position.y+0.5;
    v_TexPos = vec2(tx,ty);
}
