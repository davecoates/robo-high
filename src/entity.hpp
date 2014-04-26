#pragma once

#include <SFML/Graphics.hpp>
#include "entitymanager.hpp"

namespace rh {

    typedef unsigned int EntityID;

    class Entity 
    {
        private:
            EntityManager *em_;

            EntityID id_;

        public:

            Entity(EntityManager* em, EntityID id) : em_(em), id_(id) {}

            EntityID id() { return id_; }

            template <typename ComponentType, typename ... Args>
            ComponentType* add_component(Args && ... args) {
                return em_->add_component<ComponentType>(id_, std::forward<Args>(args) ...);
            }

            /**
             * Get a single component for an entity and return a pointer to it
             *
             * Returns nullptr if none specified
             */
            template <typename T>
            T* get_component() {
                return em_->get_component<T>(id_);
            }



    };

}
