#pragma once

#include <SFML/Graphics.hpp>

namespace rh {

    typedef unsigned int EntityID;

    class EntityManager;

    class Entity 
    {
        private:
            EntityManager *em_;

        protected:

            EntityID id_;

        public:

            Entity(EntityManager* em, EntityID id) : em_(em), id_(id) {}

            EntityID id() { return id_; }

            template <typename ComponentType, typename ... Args>
            ComponentType* add_component(Args && ... args);

            template <typename T, typename ... Ts>
            bool get_components(T* &first, Ts*&... rest);

            /**
             * Get a single component for an entity and return a pointer to it
             *
             * Returns nullptr if none specified
             */
            template <typename T>
            T* get_component();

    };

}

#include "entitymanager.hpp"

namespace rh {
    template <typename ComponentType, typename ... Args>
    ComponentType* Entity::add_component(Args && ... args) {
        return em_->add_component<ComponentType>(id_, std::forward<Args>(args) ...);
    }

    template <typename T, typename ... Ts>
    bool Entity::get_components(T* &first, Ts*&... rest) {
        return em_->get_components<T, Ts ...>(id_,first, rest ...);
    }

    template <typename T>
    T* Entity::get_component() {
        return em_->get_component<T>(id_);
    }

}
