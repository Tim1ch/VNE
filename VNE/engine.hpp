#pragma once
#include "SFML/Graphics.hpp"
#include <boost/json.hpp>
#include "state_machine.hpp"
#include "logo.hpp"
#include "menu.hpp"

class Engine {
private:
    static Engine* engine_instance;
    Engine();
    boost::json::object load_config();
    boost::json::object create_config();

    StateMachine* state_machine;
    LogoState* logo_state;
    MenuState* menu_state;
    boost::json::object config;
  
public:
    static Engine* create_instance();
    void game_loop();
};