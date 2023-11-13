#include "logo.hpp"
#include <iostream>


void LogoState::init() {
	this->ibackground.loadFromFile("../resources/logo/logo.png");
	this->tbackground.loadFromImage(this->ibackground);
	this->sbackground.setTexture(this->tbackground);

	this->sprite_content.push_back(this->sbackground);
}

void LogoState::handle(StateMachine* state_machine) {

}

void LogoState::draw_content(sf::RenderWindow* window) {
	window->draw(this->sbackground);
};