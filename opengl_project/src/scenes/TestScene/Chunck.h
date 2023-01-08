#ifndef CHUNCK_H
#define CHUNCK_H

#include "Entity.h"
#include "Renderer.h"
#include "Shader.h"
#include "Transform.h"
#include "VertexArray.h"
#include "TextureAtlas.h"
#include "ChunckManager.h"

class Chunck : public Entity
{
public:
	Chunck(glm::vec2 chunckWorldCoord);
	~Chunck();

	void Update() override;
	void Start() override;

	void UpdateChunck();
	void GenerateChunckVoxels();

	ChunckManager::Block GetBlock(glm::uvec3 localIndex);

private:

	void CreateChunckMesh();
	void AddVoxelFaces(glm::vec3 voxelIndex);

	const int m_FaceTriangulation[6]{ 3,1,0,3,2,1 };

	const int m_FaceVerticeIndexes[6][4]
	{
		{0,1,2,3}, //Top
		{7,6,5,4}, //Bottom
		{3,2,6,7}, //Front
		{1,0,4,5}, //Back
		{2,1,5,6}, //Right
		{0,3,7,4}, //Left
	};

	const glm::vec3 m_CubeVertices[8]
	{
		glm::vec3(0, 1, 0),
		glm::vec3(1, 1, 0),
		glm::vec3(1, 1, 1),
		glm::vec3(0, 1, 1),

		glm::vec3(0, 0, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 1),
		glm::vec3(0, 0, 1),
	};


	ChunckManager::Block m_Blocks [ChunckManager::m_ChunckSize][ChunckManager::m_ChunckSize][ChunckManager::m_ChunckSize];

	ChunckManager* m_ChunckManager;

	glm::vec2 m_WorldChunckCoord;
	glm::vec2 m_GlobalChunckCoord;

	int m_VerticeCount;
	int m_TriangleCount;

	//unsigned int m_Triangles[ChunckManager::m_MaxVoxelsPerChunck*6*6];
	//Mesh::Vertex m_Vertices[ChunckManager::m_MaxVoxelsPerChunck*4*6];

	unsigned int* m_Triangles;
	Mesh::Vertex* m_Vertices;

	Transform m_ChunckTransform;
	TextureAtlas* m_TextureTest;
	Mesh m_ChunckMesh;
};

#else
class Chunck;
#endif