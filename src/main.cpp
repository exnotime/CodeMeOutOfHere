#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <glm/glm.hpp>

#include "Robot.h"
#include "if_Robot.h"

#include "script/ScriptEngine.h"

using namespace glm;

void LoadCode(Robot* r, const char* filename) {
	FILE* f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int s = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* code = (char*)malloc(s + 1);
	fread(code, sizeof(char), s, f);
	fclose(f);
	code[s] = 0;
	r->InsertScript(code, s);
	free(code);
}

int main() {
	sf::RenderWindow window(sf::VideoMode(30 * 40, 30 * 40), "CodeMeOutOfHere");
	sf::Clock timer;

	sf::RectangleShape tile;
	tile.setFillColor(sf::Color::Blue);
	tile.setOutlineColor(sf::Color::Magenta);
	tile.setOutlineThickness(2.0f);
	tile.setSize(sf::Vector2<float>(30, 30));

	sf::CircleShape circle;
	circle.setFillColor(sf::Color::Red);
	circle.setRadius(1.0f);
	circle.setScale(14.0f, 14.0f);

	sf::CircleShape timerCircle;
	timerCircle.setFillColor(sf::Color::Yellow);
	timerCircle.setRadius(1.0f);
	timerCircle.setScale(30.0f, 30.0f);
	timerCircle.setPosition(window.getSize().x - 80, 50);

	Robot r;
	MoverRobot::CreateEngine(&r);
	LoadCode(&r, "test.as");

	float timerScale = 1.0f;

	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
		
			if (e.type == sf::Event::Closed || (e.key.code == sf::Keyboard::Escape && e.type == sf::Event::EventType::KeyPressed))
				window.close();

			if ((e.key.code == sf::Keyboard::R && e.type == sf::Event::EventType::KeyReleased))
				LoadCode(&r, "test.as");
		}
		//update
		float deltaTime = timer.restart().asSeconds();

		timerScale -= deltaTime;
		if (timerScale <= 0.0f) {
			timerScale = 1.0f;
		}
		timerCircle.setRadius(timerScale);
		r.Update(deltaTime);

		//draw
		window.clear(sf::Color::Black);
		//draw tiles
		for (int y = 0; y < 40; ++y) {
			for (int x = 0; x < 40; ++x) {
				tile.setPosition(sf::Vector2<float>(30 * x, 30 * y));
				window.draw(tile);
			}
		}
		//draw robots
		circle.setPosition(r.GetPos().x * 30, r.GetPos().y * 30);
		window.draw(circle);
		window.draw(timerCircle);
		window.display();
		
	}
	return 0;
}