#pragma once

#include <string>
#include <stb_image/stb_image.h>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(uint32_t slot = 0) const;
private:
	std::string m_Path;
	bool m_IsLoaded = false;
	uint32_t m_Width, m_Height;
	uint32_t m_RendererID;
};