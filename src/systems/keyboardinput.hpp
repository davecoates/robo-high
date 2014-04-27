#pragma once

#include <SFML/Window.hpp>

#include "../system.hpp"

namespace rh {

    class KeyboardInputSystem : public System {

        static constexpr sf::Uint8 EVENT_POOL_SIZE = 10;

        private:
            sf::Event::KeyEvent event_pool_[EVENT_POOL_SIZE];
            unsigned int event_count_ = 0;

        public:
            using System::System;

            void process(sf::RenderWindow *window, const EntityVector&);

            void add_event(const sf::Event::KeyEvent &event);
    };

}
