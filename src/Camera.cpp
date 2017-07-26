#include "Camera.h"
#include "Input.h"

Camera::Camera() {
	m_Position = glm::vec2(0);
	m_Area = glm::vec2(1);
	m_Viewport = glm::vec4(0, 0, 1, 1);
	m_view = sf::View();
	
}

Camera::~Camera() {

}

void Camera::Update() {
	const glm::vec2 halfArea = m_Area * 0.5f;
	m_view.setCenter(m_Position.x + halfArea.x, m_Position.y + halfArea.y);
	m_view.setSize(m_Area.x, m_Area.y);
	m_view.setViewport(sf::FloatRect(m_Viewport.x, m_Viewport.y, m_Viewport.z, m_Viewport.w));
}

void Camera::Apply(sf::RenderWindow* window) {
	window->setView(m_view);
}