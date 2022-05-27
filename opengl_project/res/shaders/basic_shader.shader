#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 i_texCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	i_texCoord = texCoord;
};

#shader fragment
#version 330 core

out vec4 color;

in vec2 i_texCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	color = texture(u_Texture, i_texCoord) * u_Color;
};