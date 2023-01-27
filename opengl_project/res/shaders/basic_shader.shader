#shader vertex
#version 410 core

layout(location = 0) in uint data;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

out vec4 v_Color;
out vec3 v_TexCoord;

vec2 texCoords[4] = vec2[4](
	vec2(0.0f, 0.0f),
	vec2(1.0f, 0.0f),
	vec2(1.0f, 1.0f),
	vec2(0.0f, 1.0f)
);

void main()
{
	float x = data & 0x1F;
	float y = (data >> 5) & 0x7F;
	float z = (data >> 12) & 0x1F;

	uint blockType = (data >> 17) & 0xF;
	uint texIndex = (data >> 21) & 3;

	v_TexCoord = vec3(texCoords[texIndex], blockType);

	gl_Position = u_ViewProjection * u_Transform * vec4(x,y,z, 1.0);
};

#shader fragment
#version 410 core

uniform sampler2DArray u_Texture;

out vec4 color;
in vec3 v_TexCoord;

void main()
{
	color = texture(u_Texture, v_TexCoord, 0);
	//color = vec4(vec3(gl_FragCoord.z), 1);
}