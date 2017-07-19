#pragma once
#include <SFML/Window.hpp>



namespace Input {
	enum KeyState {
		UP = 0b0,
		DOWN = 0b1
	};

	struct InputState {
		uint8_t  KeyStates[sf::Keyboard::KeyCount];
	};

	InputState CurrentState;
	InputState LastState;
	void Update();
	void HandleEvent(sf::Event& e);

	bool KeyDown(sf::Keyboard::Key k);
	bool KeyUp(sf::Keyboard::Key k);
	bool KeyPushed(sf::Keyboard::Key k);
	bool KeyReleased(sf::Keyboard::Key k);
};

