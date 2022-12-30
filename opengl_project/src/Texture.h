#pragma once

#include <string>
#include <stb_image/stb_image.h>
#include <gl/glew.h>

class TextureArrays;

class Texture
{
	public:
		void Bind(GLsizei slot = 0) const;
	protected:

		Texture(GLenum texType);
		~Texture();

		template <class TextureType>
		void Load(const std::string& path);

		GLsizei m_InternalFormat;
		GLsizei m_DataFormat;
		GLsizei m_Channels;
		GLsizei m_Width, m_Height;

		bool m_IsLoaded = false;
		uint32_t m_RendererID;
		std::string m_Path;
};

class TextureArray : public Texture
{
public:
	TextureArray(const std::string& path, GLsizei height, GLsizei width, GLsizei depth);
	TextureArray(GLsizei height, GLsizei width, GLsizei depth);
	~TextureArray();

	void SetImageData(stbi_uc* data);
	void SetSliceData(stbi_uc* data, GLuint zIndex);
	void Create();

protected:
	GLsizei m_TileHeight, m_TileWidth, m_TileCount;
};

class Texture2D : public Texture
{
public:
	Texture2D(const std::string& path);
	Texture2D(GLsizei height, GLsizei width);
	~Texture2D();

	void Create();
	void SetImageData(stbi_uc* data);

friend Texture;
};