#include "engine.hpp"
#include <string>
#include <fstream>
#include <iostream>

Engine * Engine::engine_instance = nullptr;

Engine * Engine::create_instance() {
    if (engine_instance == nullptr) {
        return new Engine();
    }

    return engine_instance;
}


boost::json::object Engine::create_config() {
    boost::json::object temp_config;
    temp_config["name"] = "VNE";
    temp_config["resolution"] = {1280, 720};
    temp_config["fullscreen"] = false;

    std::ofstream config_output_file("config.json");
    config_output_file << boost::json::serialize(temp_config);
    config_output_file.close();

    return temp_config;
}

boost::json::object Engine::load_config() {
    std::ifstream config_input_file("config.json");

    if (config_input_file) {
        boost::json::value temp_config = boost::json::parse(config_input_file);
        if (temp_config.is_object()) {
            return temp_config.as_object();
        }
    }
    config_input_file.close();
    return this->create_config();
}

Engine::Engine() {
    this->config = this->load_config();

    this->logo_state = new LogoState();
    this->menu_state = MenuState::create_instance();

    this->state_machine = StateMachine::create_instance(this->logo_state);

    if (this->config["fullscreen"].as_bool()) {
        this->state_machine->window = new sf::RenderWindow(sf::VideoMode(this->config["resolution"].as_array()[0].as_int64(), this->config["resolution"].as_array()[1].as_int64()), this->config["name"].as_string().c_str(), sf::Style::Fullscreen);
    } else {
        this->state_machine->window = new sf::RenderWindow(sf::VideoMode(this->config["resolution"].as_array()[0].as_int64(), this->config["resolution"].as_array()[1].as_int64()), this->config["name"].as_string().c_str(), sf::Style::Close | sf::Style::Titlebar);
    }
    this->state_machine->window->setFramerateLimit(60);
    this->state_machine->view.reset(sf::FloatRect(0, 0, 1920, 1080));

    this->state_machine->switch_state(this->menu_state);

 
}

void Engine::game_loop() {
    while (this->state_machine->window->isOpen()) {
        while (this->state_machine->window->pollEvent(this->state_machine->window_event)) {
            if (this->state_machine->window_event.type == sf::Event::Closed) {
                this->state_machine->window->close();
            }
        }
        
        this->state_machine->update();
    }
}