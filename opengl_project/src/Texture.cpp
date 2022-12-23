#include "Texture.h"
#include "Renderer.h"
#include <GL/glew.h>

Texture::Texture(const std::string& path) : m_Path(path), m_Height(0), m_Width(0), m_RendererID(-1)
{
	GLsizei tileWidth = 16;
	GLsizei tileHeight = 16;

	GLsizei imageWidth;
	GLsizei imageHeight;

	GLsizei tileCount = 4;
	GLsizei mipLevelCount = 1;

	GLsizei channels;

	stbi_set_flip_vertically_on_load(0);

	stbi_uc* data = stbi_load(path.c_str(), &imageWidth, &imageHeight, &channels, 0);

	if (data != nullptr)
	{
		m_IsLoaded = true;

		m_Width = imageWidth;
		m_Height = imageHeight;

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

		GLsizei tileColumns = imageWidth / tileWidth;
		GLsizei tileRows = imageHeight / tileHeight;

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_RendererID);

		GLCall(glTexStorage3D(GL_TEXTURE_2D_ARRAY, mipLevelCount, GL_RGBA8, tileWidth, tileHeight, tileCount));

		glPixelStorei(GL_UNPACK_ROW_LENGTH, imageWidth); // width
		glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, imageHeight); // height

		// Always set reasonable texture parameters
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		for (size_t y = 0; y < tileRows; y++)
		{
			for (size_t x = 0; x < tileColumns; x++)
			{
				size_t tileIndex = y * tileColumns + x;

				size_t pixelOffsetX = x*tileWidth;
				size_t pixelOffsetY = y*tileHeight*imageHeight;

				GLCall(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, tileIndex, tileWidth, tileHeight, 1, GL_RGBA, GL_UNSIGNED_BYTE, data + channels * (pixelOffsetX + pixelOffsetY)));
			}
		}

		stbi_image_free(data);
	}
}

void Texture::Bind(uint32_t slot) const
{
	//glBindTexture(GL_TEXTURE_2D_ARRAY, m_RendererID);
	glBindTextureUnit(slot, m_RendererID);
}

Texture::~Texture()
{
}
