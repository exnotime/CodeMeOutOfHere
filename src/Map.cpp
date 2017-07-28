#include "Map.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Map::Map() {

}

Map::~Map() {
	if (m_MapData) free(m_MapData);
}

void Map::Load(const char* filename) {
	int channels = 0;
	unsigned char* data = stbi_load(filename, &m_width, &m_Height, &channels, 4);
	m_MapData = (unsigned char*)malloc(m_width * m_Height);
	memset(m_MapData, 0x0, m_width * m_Height); //clear map to free

	for (int y = 0; y < m_Height; ++y) {
		for (int x = 0; x < m_width; ++x) {
			if (data[(y * m_width + x) * channels] > 128)
				m_MapData[(y * m_width + x)] = BLOCKED;
		}
	}
	stbi_image_free(data);
}

bool Map::IsFree(const glm::vec2& p) {
	glm::ivec2 v = glm::mod(p, glm::vec2(m_width, m_Height));
	return m_MapData[v.y * m_width + v.x] == FREE;
}

TileType Map::GetTileType(const glm::vec2& p) {
	glm::ivec2 v = glm::mod(p, glm::vec2(m_width, m_Height));
	return (TileType)m_MapData[v.y * m_width + v.x];
}