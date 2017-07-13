#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <glm/glm.hpp>

#include "Robot.h"
#include "if_Robot.h"

#include "script/ScriptEngine.h"

using namespace glm;

#define TILE_SIZE 100
#define TILE_COUNT_X 16
#define TILE_COUNT_Y 9

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
	sf::RenderWindow window(sf::VideoMode(TILE_SIZE * TILE_COUNT_X, TILE_SIZE * TILE_COUNT_Y), "CodeMeOutOfHere");
	sf::Clock timer;
	sf::Font font;

	if (!font.loadFromFile("Envy Code R.ttf")) {

	}

	sf::Text lineText;
	lineText.setFont(font);
	lineText.setCharacterSize(24);
	lineText.setFillColor(sf::Color::White);
	lineText.setPosition(TILE_COUNT_X * TILE_SIZE / 2, 20);

	sf::RectangleShape tile;
	tile.setFillColor(sf::Color::Blue);
	tile.setOutlineColor(sf::Color::Magenta);
	tile.setOutlineThickness(2.0f);
	tile.setSize(sf::Vector2<float>(TILE_SIZE, TILE_SIZE));

	sf::CircleShape circle;
	circle.setFillColor(sf::Color::Red);
	circle.setRadius(1.0f);
	circle.setScale(TILE_SIZE / 2, TILE_SIZE / 2);

	sf::CircleShape timerCircle;
	timerCircle.setFillColor(sf::Color::Yellow);
	timerCircle.setRadius(1.0f);
	timerCircle.setScale(TILE_SIZE, TILE_SIZE);
	timerCircle.setPosition(window.getSize().x - TILE_SIZE * 2, TILE_SIZE);

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
		//update robots
		r.Update(deltaTime);

		//draw
		window.clear(sf::Color::Black);
		//draw tiles
		for (int y = 0; y < TILE_COUNT_X; ++y) {
			for (int x = 0; x < TILE_COUNT_Y; ++x) {
				tile.setPosition(sf::Vector2<float>(TILE_SIZE * x, TILE_SIZE * y));
				window.draw(tile);
			}
		}
		//draw robots
		circle.setPosition(r.GetPos().x * TILE_SIZE, r.GetPos().y * TILE_SIZE);
		window.draw(circle);
		window.draw(timerCircle);
		//DrawText
		lineText.setString(r.GetCurrentLine());
		window.draw(lineText);
		window.display();
		
	}
	return 0;
}