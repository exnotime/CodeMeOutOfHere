#include "Input.h"

void Input::Update() {
	LastState = CurrentState;
}

void Input::HandleEvent(sf::Event& e) {
	if (e.type == sf::Event::EventType::KeyPressed) {
		CurrentState.KeyStates[e.key.code] = DOWN;
	}
	if (e.type == sf::Event::EventType::KeyReleased) {
		CurrentState.KeyStates[e.key.code] = UP;
	}
}

bool Input::KeyDown(sf::Keyboard::Key k) {
	return CurrentState.KeyStates[k] == DOWN;
}

bool Input::KeyUp(sf::Keyboard::Key k) {
	return CurrentState.KeyStates[k] == UP;
}

bool Input::KeyPushed(sf::Keyboard::Key k) {
	return CurrentState.KeyStates[k] == DOWN && LastState.KeyStates[k] == UP;
}

bool Input::KeyReleased(sf::Keyboard::Key k) {
	return CurrentState.KeyStates[k] == UP && LastState.KeyStates[k] == DOWN;
}