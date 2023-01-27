#pragma once

#include "Renderer.h"

#include <map>

#include <glm/glm.hpp>

class Chunck;
class ChunckManager;

class ChunckMesh
{
public:

	enum class CubeSide { Front, Back, Right, Left, Top, Bottom };

	Mesh m_Mesh;
	Chunck* m_MyChunck;

	void UpdateChunckMesh();
	void ApplyMesh();

	bool m_MeshApplied;

	ChunckMesh(Chunck* myChunck);
	~ChunckMesh();

private:

	struct VerticesIndices
	{
		int indices[4];
	};

	const std::map<CubeSide, VerticesIndices> m_FaceVerticeIndexes
	{
		{ CubeSide::Top, {0,1,2,3}},
		{ CubeSide::Bottom, {7,6,5,4}},
		{ CubeSide::Front, {3,2,6,7}},
		{ CubeSide::Back, {1,0,4,5}},
		{ CubeSide::Right, {2,1,5,6}},
		{ CubeSide::Left, {0,3,7,4}}
	};

	const int m_FaceTriangulation[6]{ 3,1,0,3,2,1 };

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

	int m_VerticeCount;
	int m_TriangleCount;

	unsigned int* m_Triangles;
	Mesh::Vertex* m_Vertices;

	ChunckManager* m_ChunckManager;

	void AddVoxelFaces(glm::vec3 localVoxelIndex);
};