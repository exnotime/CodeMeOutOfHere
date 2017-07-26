#pragma once
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
class Camera {
public:
	Camera();
	~Camera();

	void Init();
	void Update();
	void Apply(sf::RenderWindow* window);

	void Move(const glm::vec2& v) { m_Position += v; }
	void SetArea(const glm::vec2& v) { m_Area = v; }
	void SetPostion(const glm::vec2& v) { m_Position = v; }
	void SetViewport(const glm::vec4& v) { m_Viewport = v; } //in normalized coordinates

	glm::vec2 GetPosition() const { return m_Position; }
private:
	glm::vec2 m_Position;
	glm::vec2 m_Area;
	glm::vec4 m_Viewport;
	sf::View m_view;

};