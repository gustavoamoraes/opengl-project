#pragma once

#include "TextureAtlas.h"

class BlockAtlas
{
public:
	static BlockAtlas* instance()
	{
		static BlockAtlas INSTANCE;
		return &INSTANCE;
	}

	const int m_SpriteSize = 16;

	static const std::map<std::string, std::string> m_BlocksPaths;

	TextureAtlas* m_Atlas;

	void GenerateBlockAtlas();
	uint8_t GetID(std::string name);

private:
	BlockAtlas() {};
	~BlockAtlas() {};
};