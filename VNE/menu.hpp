#pragma once
#include "state_machine.hpp"
#include "button.hpp"


enum MenuPages : int {
	MAIN_PAGE	  = 0,
	RESTART_PAGE  = 1,
	SAVES_PAGE    = 2,
	OPTIONS_PAGE  = 3,
	ABOUT_US_PAGE = 4
};

enum Buttons : int {
	CONTINUE_BUTTON = 0,
	RESTART_BUTTON  = 1,
	SAVES_BUTTON    = 2,
	OPTIONS_BUTTON  = 3,
	ABOUT_US_BUTTON = 4,
	EXIT_BUTTON     = 5,
	BACK_BUTTON     = 6,
	PIZDA_BUTTON    = 7,
	PIDORA_OTVET_BUTTON = 8
};


class MenuState : public State {
private:
	static MenuState* menu_instance;
	MenuState();
	
	bool view_animation = false;
	sf::Vector2f view_end_point;

	sf::Image ibackground, isaves;
	sf::Texture tbackground, tsaves;
	sf::Sprite sbackground, ssaves;
	
	sf::Font menu_font;

	std::vector <Button> buttons;

	std::wstring restart_game_text_string = L"Вы действительно хотите начать новую игру?";
	sf::Text restart_game_text;

	std::wstring about_us_text_string = L"Тимур - кнопкодав @katen_kyokotsu_karamatsu_shinjuu\nЛёха - художник @Kohaku_desu";
	sf::Text about_us_text;

	std::wstring pizda_text_string = L"ПИЗДА)))";
	sf::Text pizda_text;

	std::wstring pidora_otvet_text_string = L"ПИДОРА\nОТВЕТ)))";
	sf::Text pidora_otvet_text;

	std::wstring options_text_string = L"пока пуста((";
	sf::Text options_text;

public:
	static MenuState* create_instance();
	void init();
	void change_page(MenuPages page, sf::View& view);
	void handle(StateMachine* state_machine);
	void draw_content(sf::RenderWindow* window);
};