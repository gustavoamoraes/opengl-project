#include "TerrainGenerator.h"

void TerrainGenerator::GenerateVoxelsForChunck(Chunck* chunck)
{
	ChunckManager::BlockIndex lastBlockVertical = Blocks::AIR.id;

	glm::uvec3 chunckSize = ChunckManager::m_ChunckSize;

	for (size_t x = 0; x < chunckSize.x; x++)
	{
		for (size_t z = 0; z < chunckSize.z; z++)
		{
			int distFromSurface = 1;

			for (int y = chunckSize.y - 1; y >= 0; y--)
			{
				glm::vec3 i(x, y, z );
				
				ChunckManager::BlockIndex currentBlock = i.y < 50 ? Blocks::ICE.id : Blocks::AIR.id;

				glm::vec3 globalVoxelIndex = glm::vec3(
					chunck->m_WorldChunckPosition.x + i.x,
					i.y,
					chunck->m_WorldChunckPosition.z + i.z);

				glm::vec3 noiseCoord = globalVoxelIndex * m_Resolution;

				float mask = (1.0f - (globalVoxelIndex.y / chunckSize.y));
				//float mask = 1.0f;

				//float noise = 1.0f;
				//float noise = mask * m_Perlin.octave3D_01(noiseCoord.x, noiseCoord.y, noiseCoord.z, m_Octaves, m_Persistance);
				float noise = mask * m_Perlin.noise3D_01(noiseCoord.x, noiseCoord.y, noiseCoord.z);
				//float noise = mask * m_Perlin.octave3D_11(noiseCoord.x, noiseCoord.y, noiseCoord.z,m_Octaves, m_Persistance);

				bool solid = noise > m_Threshold;

				distFromSurface += solid;

				if (solid)
					currentBlock = lastBlockVertical ? (distFromSurface > 3 ? Blocks::STONE.id : Blocks::DIRT.id) : Blocks::GRASS.id;

				lastBlockVertical = currentBlock;
				chunck->m_Blocks[x][y][z] = currentBlock;
			}
		}
	}

	chunck->m_VoxelsReady = true;
}