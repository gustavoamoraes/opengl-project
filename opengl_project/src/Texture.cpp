#include "Texture.h"
#include "Renderer.h"

#include <typeinfo>
#include <iostream>
#include <GL/glew.h>

template <class TextureType>
void Texture::Load(const std::string& path)
{
	stbi_set_flip_vertically_on_load(0);

	stbi_uc* data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 0);

	if (data != nullptr)
	{
		m_IsLoaded = true;

		if (m_Channels == 4)
		{
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
		}
		else if (m_Channels == 3)
		{
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
		}

		auto tex = ((TextureType*)this);
		tex->Create();
		tex->SetImageData(data);
		stbi_image_free(data);
	}
}

void Texture::Bind(GLsizei slot) const
{
	glBindTextureUnit(slot, m_RendererID);
}

Texture::Texture(GLenum texType)
{
	//glGenTextures(1, &m_RendererID);
	//glBindTexture(texType, m_RendererID);
}

Texture::~Texture()
{
}

//
//Texture Array
//

TextureArray::TextureArray(const std::string& path, GLsizei height, GLsizei width, GLsizei depth) : m_TileHeight(height),
m_TileWidth(width), m_TileCount(depth), Texture(GL_TEXTURE_2D_ARRAY)
{
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_RendererID);
	glBindTextureUnit(0, m_RendererID);
	glActiveTexture(GL_TEXTURE0);

	Texture::Load<TextureArray>(path);
}

TextureArray::TextureArray(GLsizei height, GLsizei width, GLsizei depth) : m_TileHeight(height),
m_TileWidth(width), m_TileCount(depth), Texture(GL_TEXTURE_2D_ARRAY)
{
	m_InternalFormat = GL_RGBA8;
	m_DataFormat = GL_RGBA;
	m_Channels = 4;

	Create();
}

TextureArray::~TextureArray()
{
}

void TextureArray::SetImageData(stbi_uc* data)
{
	glPixelStorei(GL_UNPACK_ROW_LENGTH, m_Width);
	glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, m_Height);

	GLsizei tileColumns = m_Width / m_TileWidth;
	GLsizei tileRows = m_Height / m_TileHeight;

	for (size_t y = 0; y < tileRows; y++)
	{
		for (size_t x = 0; x < tileColumns; x++)
		{
			size_t tileIndex = y * tileColumns + x;

			size_t pixelOffsetX = x * m_TileWidth;
			size_t pixelOffsetY = y * m_TileHeight * m_Height;

			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, tileIndex, m_TileWidth, m_TileHeight, 1, m_DataFormat, GL_UNSIGNED_BYTE,
				data + 4 * (pixelOffsetX + pixelOffsetY));
		}
	}
}

void TextureArray::SetSliceData(stbi_uc* data, GLuint zIndex)
{
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, zIndex, m_TileWidth, m_TileHeight, 1, m_DataFormat, GL_UNSIGNED_BYTE, data);
}

void TextureArray::Create()
{
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, m_InternalFormat, m_TileWidth, m_TileHeight, m_TileCount);

	//Set texture parameters
	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

//
//Texture 2D
//

Texture2D::Texture2D(const std::string& path) : Texture(GL_TEXTURE_2D)
{
	Texture::Load<Texture2D>(path);
}

Texture2D::Texture2D(GLsizei width, GLsizei height) : Texture(GL_TEXTURE_2D)
{
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	glBindTextureUnit(0, m_RendererID);
	glActiveTexture(GL_TEXTURE0);

	m_Height = height;
	m_Width = width;

	m_InternalFormat = GL_RGBA8;
	m_DataFormat = GL_RGBA;

	Create();
}

Texture2D::~Texture2D()
{
}


void Texture2D::SetImageData(stbi_uc* data)
{
	glPixelStorei(GL_UNPACK_ROW_LENGTH, m_Width);

	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
}

void Texture2D::Create()
{
	glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

	//Set texture parameters
	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
