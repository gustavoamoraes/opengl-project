#include "Blocks.h"
#include "BlockAtlas.h"

const Block* Blocks::m_AllBlocks[m_NumberOfBlocks];

const Block Blocks::AIR = AddBlock(&Blocks::AIR, { 0, "air", {} });

const Block Blocks::GRASS = AddBlock
(
	&Blocks::GRASS,
	{
		1,
		"grass",
		{
			{ChunckMesh::CubeSide::Top, BlockAtlas::instance()->GetID("grass_top")},
			{ChunckMesh::CubeSide::Bottom, BlockAtlas::instance()->GetID("dirt")},
			{ChunckMesh::CubeSide::Front, BlockAtlas::instance()->GetID("grass_side")},
			{ChunckMesh::CubeSide::Back, BlockAtlas::instance()->GetID("grass_side")},
			{ChunckMesh::CubeSide::Right, BlockAtlas::instance()->GetID("grass_side")},
			{ChunckMesh::CubeSide::Left, BlockAtlas::instance()->GetID("grass_side")},
		}
	}
);
const Block Blocks::DIRT = AddBlock
(
	&Blocks::DIRT,
	{
		2,
		"dirt",
		{
			{ChunckMesh::CubeSide::Top, BlockAtlas::instance()->GetID("dirt")},
			{ChunckMesh::CubeSide::Bottom, BlockAtlas::instance()->GetID("dirt")},
			{ChunckMesh::CubeSide::Front, BlockAtlas::instance()->GetID("dirt")},
			{ChunckMesh::CubeSide::Back, BlockAtlas::instance()->GetID("dirt")},
			{ChunckMesh::CubeSide::Right, BlockAtlas::instance()->GetID("dirt")},
			{ChunckMesh::CubeSide::Left, BlockAtlas::instance()->GetID("dirt")},
		}
	}
);