#include "menu.hpp"
#include <iostream>
#include "button.hpp"

MenuState* MenuState::menu_instance = nullptr;

MenuState::MenuState() {

}

MenuState* MenuState::create_instance() {
	if (menu_instance == nullptr) {
		return new MenuState();
	}

	return menu_instance;
}


void MenuState::init() {
	this->ibackground.loadFromFile("../resources/gui/menu/background.png");
	this->tbackground.loadFromImage(this->ibackground);
	this->sbackground.setTexture(this->tbackground);
	this->sbackground.setOrigin(960, 540);
	this->sbackground.setPosition(960, 540);

	this->isaves.loadFromFile("../resources/gui/menu/saves.png");
	this->isaves.createMaskFromColor(sf::Color(0, 255, 0));
	this->tsaves.loadFromImage(this->isaves);
	this->ssaves.setTexture(this->tsaves);
	this->ssaves.setOrigin(960, 540);
	this->ssaves.setPosition(-960, 540);

	this->menu_font.loadFromFile("C:/Windows/Fonts/comicz.ttf");

	this->buttons.push_back(*new Button(CONTINUE_BUTTON, L"Продолжить",    menu_font,  100,   90));
	this->buttons.push_back(*new Button(RESTART_BUTTON,  L"Начать заново", menu_font,  100,   180));
	this->buttons.push_back(*new Button(SAVES_BUTTON,    L"Сохранения",    menu_font,  100,   270));
	this->buttons.push_back(*new Button(OPTIONS_BUTTON,  L"Настройки",     menu_font,  100,   360));
	this->buttons.push_back(*new Button(ABOUT_US_BUTTON, L"Об авторах",    menu_font,  100,   450));
	this->buttons.push_back(*new Button(EXIT_BUTTON,     L"Выход",         menu_font,  100,   540));
	this->buttons.push_back(*new Button(BACK_BUTTON,     L"Назад",         menu_font,  1620, -980));
	this->buttons.push_back(*new Button(BACK_BUTTON,	 L"Назад",		   menu_font, -300,   100));
	this->buttons.push_back(*new Button(BACK_BUTTON,	 L"Назад",		   menu_font,  3540,  100));
	this->buttons.push_back(*new Button(BACK_BUTTON,	 L"Назад",		   menu_font,  1620,  1180));
	this->buttons.push_back(*new Button(BACK_BUTTON,	 L"Назад",		   menu_font, -300, -980));
	this->buttons.push_back(*new Button(BACK_BUTTON,	 L"Назад",		   menu_font, 3540, -980));
	this->buttons.push_back(*new Button(PIZDA_BUTTON,    L"Да",            menu_font,  640, -600));
	this->buttons.push_back(*new Button(PIDORA_OTVET_BUTTON,	 L"Нет", menu_font, 1280, -600));
	
	this->about_us_text.setString(this->about_us_text_string);
	this->about_us_text.setCharacterSize(64);
	this->about_us_text.setFillColor(sf::Color(200, 200, 200));
	this->about_us_text.setFont(this->menu_font);
	this->about_us_text.setPosition(100, 1380);

	this->restart_game_text.setString(this->restart_game_text_string);
	this->restart_game_text.setCharacterSize(64);
	this->restart_game_text.setFillColor(sf::Color(200, 200, 200));
	this->restart_game_text.setFont(this->menu_font);
	this->restart_game_text.setPosition(175, -840);

	this->pizda_text.setString(this->pizda_text_string);
	this->pizda_text.setCharacterSize(380);
	this->pizda_text.setFillColor(sf::Color(200, 200, 200));
	this->pizda_text.setFont(this->menu_font);
	this->pizda_text.setPosition(-1920, -900);

	this->pidora_otvet_text.setString(this->pidora_otvet_text_string);
	this->pidora_otvet_text.setCharacterSize(300);
	this->pidora_otvet_text.setFillColor(sf::Color(200, 200, 200));
	this->pidora_otvet_text.setFont(this->menu_font);
	this->pidora_otvet_text.setPosition(1920, -1000);

	this->options_text.setString(this->options_text_string);
	this->options_text.setCharacterSize(100);
	this->options_text.setFillColor(sf::Color(200, 200, 200));
	this->options_text.setFont(this->menu_font);
	this->options_text.setPosition(2550, 420);

}

void MenuState::change_page(MenuPages page, sf::View& view) {
	sf::Vector2i end_view_pos(0, 0);
	switch (page) {
	case RESTART_PAGE:
		end_view_pos.x = 960;
		end_view_pos.y = -540;
		break;
	case SAVES_PAGE:
		end_view_pos.x = -960;
		end_view_pos.y = 540;
		break;
	case OPTIONS_PAGE:
		end_view_pos.x = 2880;
		end_view_pos.y = 540;
		break;
	case ABOUT_US_PAGE:
		end_view_pos.x = 960;
		end_view_pos.y = 1620;
		break;
	case MAIN_PAGE:
		end_view_pos.x = 960;
		end_view_pos.y = 540;
	}

	this->view_animation = true;
	this->view_end_point = sf::Vector2f(end_view_pos);
}

void MenuState::handle(StateMachine* state_machine) {
	if (view_animation) {
		if (abs(this->view_end_point.x - state_machine->view.getCenter().x) > 10) {
			if (this->view_end_point.x - state_machine->view.getCenter().x < 10) {
				state_machine->view.move(-40, 0);
			} 
			if (this->view_end_point.x - state_machine->view.getCenter().x > 10) {
				state_machine->view.move(40, 0);
			}
		} else if (abs(this->view_end_point.y - state_machine->view.getCenter().y) > 10) {
			if (this->view_end_point.y - state_machine->view.getCenter().y < 10) {
				state_machine->view.move(0, -30);
			}
			if (this->view_end_point.y - state_machine->view.getCenter().y > 10) {
				state_machine->view.move(0, 30);
			}
		} else {
			state_machine->view.setCenter(view_end_point);
			view_animation = false;
		}
		sbackground.setPosition(state_machine->view.getCenter());
	} else {
		for (Button& button_iter : this->buttons) {
			if (button_iter.contains(state_machine->window_event, *state_machine->window)) {
				button_iter.set_text_color(sf::Color(0, 255, 200, 200));
			}
			else {
				button_iter.set_text_color(sf::Color(255, 255, 255, 200));
			}

			if (button_iter.click_on(state_machine->window_event, *state_machine->window)) {
				switch (button_iter.type) {
				case CONTINUE_BUTTON:
					break;
				case RESTART_BUTTON:
					this->change_page(RESTART_PAGE, state_machine->view);
					break;
				case SAVES_BUTTON:
					this->change_page(SAVES_PAGE, state_machine->view);
					break;
				case OPTIONS_BUTTON:
					this->change_page(OPTIONS_PAGE, state_machine->view);
					break;
				case ABOUT_US_BUTTON:
					this->change_page(ABOUT_US_PAGE, state_machine->view);
					break;
				case EXIT_BUTTON:
					std::exit(0);
					break;
				case BACK_BUTTON:
					this->change_page(MAIN_PAGE, state_machine->view);
					break;
				case PIZDA_BUTTON:
					state_machine->view.setCenter(-960, -540);
					break;
				case PIDORA_OTVET_BUTTON:
					state_machine->view.setCenter(2880, -540);
					break;
				}
			}
		}
	}
}

void MenuState::draw_content(sf::RenderWindow* window) {
	window->draw(this->sbackground);
	window->draw(this->ssaves);
	for (Button& button_iter : this->buttons) {
		window->draw(button_iter.get_text());
	}
	window->draw(this->restart_game_text);
	window->draw(this->about_us_text);
	window->draw(this->pizda_text);
	window->draw(this->pidora_otvet_text);
	window->draw(this->options_text);
};