#pragma once

#include "Chunck.h"
#include "ChunckManager.h"
#include "Blocks.h"
#include "perlin_noise/PerlinNoise.hpp"

class TerrainGenerator 
{
public:

	TerrainGenerator(unsigned int terrainSeed) : m_TerrainSeed(terrainSeed)
	{
	}

	void GenerateVoxelsForChunck(Chunck* chunck)
	{
		ChunckManager::BlockIndex lastBlockVertical = Blocks::AIR.id;

		glm::uvec3 chunckSize = ChunckManager::m_ChunckSize;

		for (size_t x = 0; x < chunckSize.x; x++)
		{
			for (size_t z = 0; z < chunckSize.z; z++)
			{
				int distFromSurface = 0;

				for (int y = chunckSize.y-1; y >=0; y--)
				{
					ChunckManager::BlockIndex currentBlock = y < 64 ? Blocks::ICE.id : Blocks::AIR.id;

					glm::vec3 globalVoxelIndex = glm::vec3(chunck->m_WorldChunckCoord.x * chunckSize.x + x,
						y,
						chunck->m_WorldChunckCoord.y * chunckSize.z + z);

					glm::vec3 noiseCoord = globalVoxelIndex * m_Resolution;

					float mask = 1.0f - (globalVoxelIndex.y / chunckSize.y);
					float noise = mask * m_Perlin.octave3D_01(noiseCoord.x, noiseCoord.y, noiseCoord.z, m_Octaves, m_Persistance);
					bool solid = noise > m_Threshold;

					distFromSurface += solid;

					if(solid)
						currentBlock = lastBlockVertical ? (distFromSurface > 3 ? Blocks::STONE.id : Blocks::DIRT.id)  : Blocks::GRASS.id;

					lastBlockVertical = currentBlock;
					chunck->m_Blocks[x][y][z] = currentBlock;
				}
			}
		}
	}

private:

	const siv::PerlinNoise::seed_type m_TerrainSeed;
	const siv::PerlinNoise m_Perlin { m_TerrainSeed };

	const float m_Resolution = 1.0f / 50.0f;
	const int m_Octaves = 5;
	const float m_Persistance = 0.25f;
	const float m_Threshold = 0.2f;
};