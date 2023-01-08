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

	static const size_t m_ChunckSize = 31;

	Block getBlockGlobal(glm::vec3 globalVoxelIndex);

	void GenerateChuncks();

	void Start() override;

private:
	ChunckManager();
	~ChunckManager();

	const unsigned char m_ChunckRadius = 4;

	static const size_t m_ChuncksWidth = 4;
	static const size_t m_ChuncksHeight = 4;
	static const unsigned int m_MaxVoxelsPerChunck = (m_ChunckSize * m_ChunckSize * m_ChunckSize * 1/2) - (m_ChunckSize%2 == 0);

	Chunck* m_Chuncks[m_ChuncksWidth][m_ChuncksHeight];

friend Chunck;
};

#else
class ChunckManager;
#endif