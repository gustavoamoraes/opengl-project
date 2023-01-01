#pragma once

#include <string>
#include <stb_image/stb_image.h>
#include <gl/glew.h>

class TextureArrays;

class TextureAtlas
{
	public:
		void Bind() const;
		void SetSlot(GLsizei slot = 0);

		TextureAtlas(const std::string path, GLsizei height, GLsizei width, GLsizei depth, GLsizei slot);
		~TextureAtlas();

	private:

		void Load();
		void SetData(stbi_uc* data);
		void Create();

		uint32_t m_RendererID;
		std::string m_Path;
		bool m_IsLoaded = false;

		GLsizei m_InternalFormat;
		GLsizei m_DataFormat;
		GLsizei m_Channels;
		GLsizei m_Width, m_Height;
		GLsizei m_Slot;

		GLsizei m_TileHeight, m_TileWidth, m_TileCount;
};