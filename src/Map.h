#pragma once
#include <glm/glm.hpp>
enum TileType {
	FREE,
	BLOCKED
};

class Map {
public:
	Map();
	~Map();
	void Load(const char* filename);
	bool IsFree(const glm::vec2& p);
	TileType GetTileType(const glm::vec2& p);

	int GetWidth() { return m_width; }
	int GetHeight() { return m_Height; }

private:
	unsigned char* m_MapData;
	int m_width;
	int m_Height;
};