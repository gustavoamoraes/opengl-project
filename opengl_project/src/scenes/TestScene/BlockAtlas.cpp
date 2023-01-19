#include "BlockAtlas.h"

const std::map<std::string, std::string> BlockAtlas::m_BlocksPaths
{
	{ "grass_top", "res/textures/blocks/grass_top.png" },
	{ "grass_side", "res/textures/blocks/grass_side.png" },
	{ "stone", "res/textures/blocks/stone.png" },
	{ "dirt", "res/textures/blocks/dirt.png" },
	{ "ice", "res/textures/blocks/ice.png" },
};

void BlockAtlas::GenerateBlockAtlas()
{
	std::vector < std::string > paths;

	for (const auto &e : m_BlocksPaths)
		paths.push_back(e.second);

	m_Atlas = new TextureAtlas(m_SpriteSize, m_SpriteSize, m_BlocksPaths.size(), 0);
	m_Atlas->LoadTextures(paths);
}

uint8_t BlockAtlas::GetID(std::string name)
{
	return std::distance(m_BlocksPaths.begin(), m_BlocksPaths.find(name));
}