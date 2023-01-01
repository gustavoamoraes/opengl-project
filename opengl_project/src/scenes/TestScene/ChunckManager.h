#ifndef CHUNCK_MANAGER_H
#define CHUNCK_MANAGER_H

#include "Entity.h"

class Chunck;

class ChunckManager : public Entity
{
public:
	typedef unsigned char Block;

	static ChunckManager* instance()
	{
		static ChunckManager INSTANCE;
		return &INSTANCE;
	}

	static const size_t m_ChunckSize = 16;

	Block getBlockGlobal(glm::uvec3 globalVoxelIndex);

	void GenerateChuncks();

	void Start() override;

private:
	ChunckManager();
	~ChunckManager();

	const unsigned char m_ChunckRadius = 4;

	static const size_t m_ChuncksWidth = 1;
	static const size_t m_ChuncksHeight = 1;

	Chunck* m_Chuncks[m_ChuncksWidth][m_ChuncksHeight];
};

#else
class ChunckManager;
#endif