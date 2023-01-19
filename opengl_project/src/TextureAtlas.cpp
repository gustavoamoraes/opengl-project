#include "TextureAtlas.h"
#include "Renderer.h"

#include <typeinfo>
#include <iostream>
#include <GL/glew.h>

TextureAtlas::TextureAtlas(GLsizei height, GLsizei width, GLsizei depth, GLsizei slot) : 
	m_Slot(slot), m_TileHeight(height), m_TileWidth(width), m_TileCount(depth)
{
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_RendererID);

	glBindTextureUnit(slot, m_RendererID);
	SetActive();

	//Create 3D texture
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, width, height, depth);

	//Set texture parameters
	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

TextureAtlas::~TextureAtlas()
{
}

void TextureAtlas::LoadTextures(const std::vector<std::string> paths)
{
	int i = 0;

	for (std::string path : paths)
	{
		auto data = Load(path);

		if (data != nullptr)
		{
			SetDataAt(data, i);
			stbi_image_free(data);
			i++;
		}
	}
}

stbi_uc* TextureAtlas::Load(std::string path)
{
	stbi_set_flip_vertically_on_load(0);

	int height, width, channels;

	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

	//if (height != m_TileHeight || width != m_TileWidth || channels != 4)
	//	return nullptr;

	return data;
}

void TextureAtlas::SetActive() const
{
	glActiveTexture(GL_TEXTURE0 + m_Slot);
}

void TextureAtlas::SetDataAt(stbi_uc* data, int index)
{
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, index, m_TileWidth, m_TileHeight, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
}