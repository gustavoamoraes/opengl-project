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

const Block Blocks::STONE = AddBlock
(
	&Blocks::STONE,
	{
		3,
		"stone",
		{
			{ChunckMesh::CubeSide::Top, BlockAtlas::instance()->GetID("stone")},
			{ChunckMesh::CubeSide::Bottom, BlockAtlas::instance()->GetID("stone")},
			{ChunckMesh::CubeSide::Front, BlockAtlas::instance()->GetID("stone")},
			{ChunckMesh::CubeSide::Back, BlockAtlas::instance()->GetID("stone")},
			{ChunckMesh::CubeSide::Right, BlockAtlas::instance()->GetID("stone")},
			{ChunckMesh::CubeSide::Left, BlockAtlas::instance()->GetID("stone")},
		}
	}
);

const Block Blocks::ICE = AddBlock
(
	&Blocks::ICE,
	{
		4,
		"ice",
		{
			{ChunckMesh::CubeSide::Top, BlockAtlas::instance()->GetID("ice")},
			{ChunckMesh::CubeSide::Bottom, BlockAtlas::instance()->GetID("ice")},
			{ChunckMesh::CubeSide::Front, BlockAtlas::instance()->GetID("ice")},
			{ChunckMesh::CubeSide::Back, BlockAtlas::instance()->GetID("ice")},
			{ChunckMesh::CubeSide::Right, BlockAtlas::instance()->GetID("ice")},
			{ChunckMesh::CubeSide::Left, BlockAtlas::instance()->GetID("ice")},
		}
	}
);