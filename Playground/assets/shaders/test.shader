#type vertex
#version 400

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;

void main()
{
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type pixel
#version 400

out vec4 color;

uniform vec4 u_Color;

void main()
{
	color = u_Color;
}