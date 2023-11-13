#pragma once
#include "state_machine.hpp"
#include "menu.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>

class LogoState : public State {
private:
	MenuState* next_state;
	sf::Image ibackground;
	sf::Texture tbackground;
	sf::Sprite sbackground;
	std::vector <sf::Sprite> sprite_content;
public:
	void init();
	void handle(StateMachine* state_machine);
	void draw_content(sf::RenderWindow* window);
};