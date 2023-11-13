#pragma once
#include "SFML/Graphics.hpp"
#include <string>

class Button {
private:
	sf::Text text;
public:
	int type;
	Button(int type, std::wstring str, sf::Font& font, int xpos, int ypos);
	sf::Text get_text();
	bool click_on(sf::Event& event, sf::RenderWindow& window);
	bool contains(sf::Event& event, sf::RenderWindow& window);
	void set_text_color(sf::Color color);

};