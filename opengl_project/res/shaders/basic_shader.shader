#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
//layout(location = 2) in vec4 color;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;
//out vec4 v_VertexColor;
out vec2 v_TexCoord;
out vec3 v_Position;

void main()
{
	//u_VertexColor = color;
	v_TexCoord = a_TexCoord;
	gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0);
	v_Position = position;
};

#shader fragment
#version 330 core

out vec4 color;
//in vec4 v_VertexColor;
in vec2 v_TexCoord;
in vec3 v_Position;

uniform vec4 u_Color;
uniform sampler2DArray u_Texture;

void main()
{
	//color = texture(u_Texture, vec3(v_TexCoord.xy, ceil(v_TexCoord.z)), 0);
	color = vec4(floor(v_Position.z),0,0, 1.0);
};