#pragma once

#include <SFML/Graphics.hpp>
#include "component.hpp"
#include "basenode.hpp"

namespace rh {


    class System {

        protected:
            void *em_;

        public:
            System(void *em) : em_(em) {};

            virtual void process(sf::RenderWindow *window) = 0;

            virtual void init_component(const unsigned int&, BaseComponent*) {}

            virtual void init() {}

            virtual void add_node(BaseNode*) {
                // TODO:
            }
    };

}
