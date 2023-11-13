#pragma once
#include <SFML/Graphics.hpp>

class StateMachine;

class State {
protected:
	std::vector <sf::Sprite> sprite_content;
	std::vector <sf::Text> text_content;
public:
	State* next_state;
	virtual void init();
	virtual void handle(StateMachine* state_machine);
	virtual  void draw_content(sf::RenderWindow* window);
};

class StateMachine {
private:
	static StateMachine* state_machine_instance;
	StateMachine(State* state);
public:
	sf::Event window_event;
	sf::RenderWindow* window;
	sf::View view;
	State* current_state;
	static StateMachine* create_instance(State * state);
	void switch_state(State* state);
	void update();
};