#pragma once

#include <string>
#include <map>
#include <vector>

#include <stb_image/stb_image.h>
#include <gl/glew.h>

class TextureAtlas
{
	public:

		TextureAtlas(GLsizei height, GLsizei width, GLsizei depth, GLsizei slot);
		~TextureAtlas();

		void LoadTextures(const std::vector<std::string> textures);
		void SetActive() const;

	private:
		stbi_uc* Load(std::string path);

		void SetDataAt(stbi_uc* data, int index);

		uint32_t m_RendererID;

		GLsizei m_Slot;
		GLsizei m_TileHeight, 
			m_TileWidth, 
			m_TileCount;
};