#pragma once

#include <vector>
#include <atomic>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "component.hpp"
#include "constants.hpp"

namespace rh {

    typedef unsigned int EntityID;

    class Entity;

    class System;

    typedef std::vector<Entity> EntityVector; 

    class EntityManager {

        private:
            std::vector<std::unique_ptr<System>> systems_;

            std::vector<ComponentMask> component_masks_;
            std::vector<std::vector<std::shared_ptr<BaseComponent>>> components_;

            std::atomic<EntityID> next_entity_id_;

            /**
             * Generate component mask AND set component_ptr to matching
             * pointer (if any). We are mixing concerns a little bit here. What
             * we want to do is generate a mask that represents a list of
             * components. We use this to test against a entity to see if it
             * has all the components. We then need a way to get all the
             * relevant components for that entity - so we just do it as we go
             * and assign it to a pointer.
             *
             * @param entity_id this is used to determine whether we set
             * component_ptr or not.
             * @param component_ptr pointer to a component - will be set if
             * entity has this component
             *
             * @return ComponentMask
             */
            template <typename T>
            ComponentMask create_component_mask(const EntityID entity_id, T* &component_ptr) {
                auto group_id = Component<T>::get_group_id();
                ComponentMask mask = 1 << group_id;
                if (mask == (mask & component_masks_[entity_id])) {
                    component_ptr = dynamic_cast<T*>(components_[group_id][entity_id].get());
                }
                return mask;
            }

            /**
             * We recursively reduce until we have a single template argument
             * which is handled above.
             *
             * @see create_component_mask() above
             */
            template <typename T1, typename T2, typename ... Ts>
            ComponentMask create_component_mask(const EntityID entity_id, T1* &first, T2* &second, Ts*&... rest) {
                return create_component_mask<T1>(entity_id, first) | 
                    create_component_mask<T2, Ts...>(entity_id, second, rest...);
            }


        public:


            EntityID generate_entity_id() {
                auto id = next_entity_id_.fetch_add(1);
                if (component_masks_.size() <= id) {
                    component_masks_.resize(id+1);
                }
                component_masks_[id] = 0;
                return id;
            }


            // Create a new Entity. This just holds an Entity ID and provides
            // some helper functions. When the object is destroyed the Entity
            // will still exist.
            Entity create_entity();

            // Create instance of an Entity using a custom Entity class. Note
            // that this dynamically allocates storage for it.
            template <typename EntityType>
                std::shared_ptr<EntityType> create_entity() {
                    return std::shared_ptr<EntityType>(
                            new EntityType(this, generate_entity_id()));
                }


            // TODO: Remove entity
            // TODO: Reuse entity id's
            // TODO: ID's or Objects??
            // TODO: OBject could just be simply wrapper around ID? Think about
            // how stuff will be isntantiated. Components contain data and
            // systems process the data. Is there a need for an object? Could
            // Robo not be replaced by a collection of components?

            /**
             * Add a component to an entity, optionally passing through
             * arguments to the components
             *
             * @param entity_id 
             * @param Args... arguments to pass to component
             */
            template <typename ComponentType, typename ... Args>
            ComponentType* add_component(const EntityID entity_id, Args && ... args) {
                if (entity_id >= next_entity_id_) {
                    throw std::runtime_error("Can't add component to invalid entity id");
                }
                auto ptr = std::shared_ptr<ComponentType>(
                        new ComponentType(std::forward<Args>(args) ...));
                auto group_id = ptr->get_group_id();
                if (components_.size() <= group_id) {
                    components_.resize(group_id + 1);
                }
                if (components_[group_id].size() <= entity_id) {
                    components_[group_id].resize(entity_id+1);
                }
                components_[group_id][entity_id] = ptr;

                component_masks_[entity_id] |= 1 << group_id;

                init_component(entity_id, ptr.get());

                return ptr.get();
            }

            /**
             * Get a single component for an entity and return a pointer to it
             *
             * Returns nullptr if none specified
             */
            template <typename T>
            T* get_component(const EntityID entity_id) {
                auto group_id = Component<T>::get_group_id();

                if (!component_masks_[entity_id].test(group_id)) {
                    return nullptr;
                }

                return dynamic_cast<T*>(components_[group_id][entity_id].get());
            }

            /**
             * Get all specific components for an entity
             *
             * Components pointers are assigned to the provided pointer ref
             * arguments.
             *
             * Note that each pointer will be set if the entity has that
             * component even if the entity doesn't have ALL components. In
             * this way you can use the return value (bool) to detect if it has
             * all components but still use available components if necessary.
             */
            template <typename T, typename ... Ts>
            bool get_components(const EntityID entity_id, T* &first, Ts*&... rest) {
                auto mask = create_component_mask<T, Ts...>(entity_id, first, rest...);
                return (mask == (component_masks_[entity_id] & mask));
            }


            const EntityVector get_entities(); 

            ///////////////////////////////////////////////////////////////////

            void init_component(const unsigned int&, BaseComponent*);

            template <typename SystemType, typename ... Args>
            SystemType* create_system(Args && ... args) {
                // TODO: Remove return value (i think). Should be doing things
                // through entities etc
                auto ptr = new SystemType(this);
                ptr->init(std::forward<Args>(args) ...);
                systems_.push_back(std::unique_ptr<SystemType>(ptr));
                return ptr;
            }

            ///////////////////////////////////////////////////////////////////
            void process(sf::RenderWindow *window);     

    };
}

// This is because we have forward declared Entity above. If we don't do this
// any class that include EntityManager would also need to include Entity
// otherwise the compiler will give errors 
#include "entity.hpp"
