#type vertex
#version 400

layout(location = 0) in vec3 a_Pos;

void main()
{
	gl_Position = vec4(a_Pos, 1.0);
}

#type pixel
#version 400

uniform vec4 u_Color;
out vec4 color;

void main()
{
	color = u_Color;
}