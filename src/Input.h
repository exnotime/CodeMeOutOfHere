#pragma once
#include <SFML/Window.hpp>

enum KeyState {
	UP = 0b0,
	DOWN = 0b1
};

struct InputState {
	uint8_t  KeyStates[sf::Keyboard::KeyCount];
};

void UpdateInput(sf::Window& w);

bool KeyDown(sf::Keyboard::Key k); 
bool KeyPushed(sf::Keyboard::Key k);
