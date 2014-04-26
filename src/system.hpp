#pragma once

#include <SFML/Graphics.hpp>
#include "component.hpp"
#include "entitymanager.hpp"

namespace rh {


    typedef unsigned int EntityID;

    class Entity;
    class EntityManager;

    typedef std::vector<Entity> EntityVector; 

    class System {

        protected:
            EntityManager *em_;

        public:
            System(EntityManager *em) : em_(em) {};

            virtual void process(sf::RenderWindow *window, const EntityVector&) = 0;

            virtual void init_component(const unsigned int&, BaseComponent*) {}

            virtual void init() {}
    };

}
