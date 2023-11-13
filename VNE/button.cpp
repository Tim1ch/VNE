#include "button.hpp"
#include <iostream>

Button::Button(int type, std::wstring str, sf::Font& font, int xpos, int ypos) {
	this->type = type;
	this->text.setCharacterSize(64);
	this->text.setFillColor(sf::Color(255, 255, 255, 200));
	this->text.setString(str);
	this->text.setFont(font);
	this->text.setPosition(xpos, ypos);
}

sf::Text Button::get_text() {
	return this->text;
}

bool Button::contains(sf::Event& event, sf::RenderWindow& window) {
	if (this->text.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
		return true;
	}
	return false;
}

bool Button::click_on(sf::Event& event, sf::RenderWindow& window) {
	if (this->text.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
		if (event.type == sf::Event::MouseButtonReleased || event.key.code == sf::Mouse::Left) {
			return true;
		}

	}
	return false;
}

void Button::set_text_color(sf::Color color) {
	this->text.setFillColor(color);
}