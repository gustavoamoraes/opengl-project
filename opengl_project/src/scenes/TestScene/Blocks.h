#pragma once

#include "ChunckMesh.h"

struct Block
{
	uint8_t id;
	std::string blockName;
	std::map<ChunckMesh::CubeSide, int> atlasIndices;
};

class Blocks
{
public:
	const static int m_NumberOfBlocks = 3;
	static const Block* m_AllBlocks[m_NumberOfBlocks];

	static const Block AIR;
	static const Block GRASS;
	static const Block DIRT;

	static const Block AddBlock(const Block* memberPointer, const Block newBlock)
	{
		m_AllBlocks[newBlock.id] = memberPointer;
		return newBlock;
	}
};