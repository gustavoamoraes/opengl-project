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

	~TerrainGenerator() 
	{
	}

	void GenerateVoxelsForChunck(Chunck* chunck);

private:

	const siv::PerlinNoise::seed_type m_TerrainSeed;
	const siv::PerlinNoise m_Perlin { m_TerrainSeed };

	const float m_Resolution = 1.0f / 50.0f;
	const int m_Octaves = 5;
	const float m_Persistance = 0.25f;
	const float m_Threshold = 0.24f;
};