#include "Texture.h"

#include <GL/glew.h>

Texture::Texture(const std::string& path) : m_Path(path)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(0);

	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);;

	if (data != nullptr)
	{
		m_IsLoaded = true;

		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;

		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}
}

void Texture::Bind(uint32_t slot) const
{
	glBindTextureUnit(slot, m_RendererID);
}

Texture::~Texture()
{
}