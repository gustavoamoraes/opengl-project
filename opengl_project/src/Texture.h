#pragma once

#include <string>

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	void* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& filepath);
	~Texture();

	void Bind(unsigned int slot) const;
	void Unbind() const;
};