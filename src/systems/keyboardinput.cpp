#include "keyboardinput.hpp"
#include "../components/movement.hpp"
#include "../components/physics.hpp"
#include <iostream>
#include <stdexcept>
#include <iostream>

namespace rh {

    void KeyboardInputSystem::process(sf::RenderWindow *window, const EntityVector&) {

        if (event_count_) {
            for (unsigned int i =0; i < event_count_;i++) {
                auto &key = event_pool_[i];
                switch (key.code) {
                    case  sf::Keyboard::Escape:
                        window->close();
                        break;
                    default:
                        break;
                }
            }
            event_count_ = 0;
        }
    }

    void KeyboardInputSystem::add_event(const sf::Event::KeyEvent &event) {
        if (event_count_ >= EVENT_POOL_SIZE) {
            throw std::runtime_error("Keyboard events exceed pool size");
        }
        event_pool_[event_count_].code = event.code;
        event_pool_[event_count_].alt = event.alt;
        event_pool_[event_count_].control = event.control;
        event_pool_[event_count_].shift = event.shift;
        event_pool_[event_count_].system = event.system;
        event_count_ = event_count_ + 1;
    }

}
