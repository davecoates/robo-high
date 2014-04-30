#pragma once

#include <SFML/Graphics.hpp>
#include "component.hpp"
#include "basenode.hpp"

namespace rh {

    class EntityManager;

    class System {

        protected:
            EntityManager *em_;

        public:
            System(EntityManager *em);

            virtual void process(sf::RenderWindow *window) = 0;

            virtual void init_component(const unsigned int&, BaseComponent*) {}

            virtual void init() {}

            virtual void add_node(BaseNode*) {}

            virtual void remove_node(BaseNode*) {}
    };

}
