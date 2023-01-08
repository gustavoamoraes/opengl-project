#include "TextureAtlas.h"
#include "Renderer.h"

#include <typeinfo>
#include <iostream>
#include <GL/glew.h>

TextureAtlas::TextureAtlas(const std::string path, GLsizei height, GLsizei width, GLsizei depth, GLsizei slot) : 
	m_TileWidth(width), m_TileHeight(height), m_TileCount(depth), m_Slot(slot), m_Path(path)
{
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_RendererID);

	SetSlot(m_Slot);
	Bind();

	Load(); 
}

TextureAtlas::~TextureAtlas()
{
}

void TextureAtlas::Load()
{
	stbi_set_flip_vertically_on_load(0);

	stbi_uc* data = stbi_load(m_Path.c_str(), &m_Width, &m_Height, &m_Channels, 0);

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

		Create();
		SetData(data);

		stbi_image_free(data);
	}
}

void TextureAtlas::SetSlot(GLsizei slot)
{
	m_Slot = slot;
	glBindTextureUnit(m_Slot, m_RendererID);
}

void TextureAtlas::Bind() const
{
	glActiveTexture(GL_TEXTURE0 + m_Slot);
}

void TextureAtlas::SetData(stbi_uc* data)
{
	GLsizei tileColumns = m_Width / m_TileWidth;
	GLsizei tileRows = m_Height / m_TileHeight;

	glPixelStorei(GL_UNPACK_ROW_LENGTH, m_Width);
	glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, m_Height);

	for (size_t y = 0; y < tileRows; y++)
	{
		for (size_t x = 0; x < tileColumns; x++)
		{
			size_t tileIndex = y * tileColumns + x;

			size_t pixelOffsetX = x * m_TileWidth;
			size_t pixelOffsetY = y * m_TileHeight * m_Height;

			//+1 because index 0 is for air
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, tileIndex + 1, m_TileWidth, m_TileHeight, 1, m_DataFormat, GL_UNSIGNED_BYTE,
				data + m_Channels * (pixelOffsetX + pixelOffsetY));
		}
	}
}

void TextureAtlas::Create()
{
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, m_InternalFormat, m_TileWidth, m_TileHeight, m_TileCount+1);

	//Set texture parameters
	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}