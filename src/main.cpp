#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <glm/glm.hpp>

#include "Robot.h"
#include "if_Robot.h"
#include "Input.h"
#include "script/ScriptEngine.h"

using namespace glm;

#define TILE_SIZE 100
#define TILE_COUNT_X 9
#define TILE_COUNT_Y 9

void LoadCode(Robot* r, const char* filename) {
	FILE* f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int s = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* code = (char*)malloc(s + 1);
	fread(code, sizeof(char), s, f);
	fclose(f);
	code[s] = 0; // make sure the string ends
	r->InsertScript(code, s);
	free(code);
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1600,900), "CodeMeOutOfHere");
	sf::Clock timer;
	sf::Font font;
	glm::vec2 codeStartPos;

	if (!font.loadFromFile("Envy Code R.ttf")) {

	}

	sf::Text lineText;
	lineText.setFont(font);
	lineText.setCharacterSize(24);
	lineText.setFillColor(sf::Color::White);
	codeStartPos = glm::vec2(TILE_COUNT_X * TILE_SIZE + 10, 20);

	sf::ConvexShape triangleShape;
	triangleShape.setPointCount(3);
	triangleShape.setPoint(0, sf::Vector2f(0, 0));
	triangleShape.setPoint(1, sf::Vector2f(1, 0.5f));
	triangleShape.setPoint(2, sf::Vector2f(0, 1));
	triangleShape.setFillColor(sf::Color::Red);
	triangleShape.setScale(20.0f, 20.0f);

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
		Input::Update();

		sf::Event e;
		while (window.pollEvent(e)) {
		
			if (e.type == sf::Event::Closed || (e.key.code == sf::Keyboard::Escape && e.type == sf::Event::EventType::KeyPressed))
				window.close();

			Input::HandleEvent(e);
		}
		//update
		float deltaTime = timer.restart().asSeconds();
		timerScale -= deltaTime;
		if (timerScale <= 0.0f) {
			timerScale = 1.0f;
		}
		timerCircle.setRadius(timerScale);
		if (Input::KeyPushed(sf::Keyboard::Key::R))
			LoadCode(&r, "test.as");

		//update robots
		r.Update(deltaTime);

		//draw
		window.clear(sf::Color::Black);
		//draw tiles
		for (int y = 0; y < TILE_COUNT_Y; ++y) {
			for (int x = 0; x < TILE_COUNT_X; ++x) {
				tile.setPosition(sf::Vector2<float>(TILE_SIZE * x, TILE_SIZE * y));
				window.draw(tile);
			}
		}
		//draw robots
		circle.setPosition(r.GetPos().x * TILE_SIZE, r.GetPos().y * TILE_SIZE);
		window.draw(circle);
		window.draw(timerCircle);

		//DrawText
		int i = 0;
		auto& code = r.GetCode();
		for (auto& l : code) {
			lineText.setPosition(codeStartPos.x + 20, codeStartPos.y + i * lineText.getCharacterSize());
			lineText.setString(l);
			if (i == r.GetCurrentLineIndex()) {
				lineText.setFillColor(sf::Color::Green);
			}
			else {
				lineText.setFillColor(sf::Color::White);
			}
			window.draw(lineText);
			i++;
		}
		
		//draw current line triangle
		triangleShape.setPosition(codeStartPos.x, codeStartPos.y + r.GetCurrentLineIndex() * lineText.getCharacterSize() + 5);
		window.draw(triangleShape);
		window.display();
		
	}
	return 0;
}