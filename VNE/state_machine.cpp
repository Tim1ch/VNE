#include "state_machine.hpp"


StateMachine* StateMachine::state_machine_instance = nullptr;

StateMachine* StateMachine::create_instance(State* state) {
	if (state_machine_instance == nullptr) {
		return new StateMachine(state);
	}
	
	return state_machine_instance;
}

StateMachine::StateMachine(State* state) {
	this->current_state = state;
	this->current_state->init();
}


void StateMachine::switch_state(State* state) {
	this->current_state = state;
	this->current_state->init();
}

void StateMachine::update() {
	this->current_state->handle(this);

	this->window->setView(this->view);
	this->window->clear(sf::Color(0, 0, 0));
	this->current_state->draw_content(window);

	this->window->display();
}

void State::init() {}
void State::handle(StateMachine* state_machine) {}
void State::draw_content(sf::RenderWindow* window) {};
