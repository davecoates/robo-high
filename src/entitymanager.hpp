#pragma once

#include <vector>
#include <atomic>
#include <list>
#include <iostream>
#include <typeinfo>

#include <SFML/Graphics.hpp>

#include "component.hpp"
#include "constants.hpp"
#include "basenode.hpp"
#include "system.hpp"

namespace rh {

    typedef unsigned int EntityID;

    class Entity;

    typedef std::vector<Entity> EntityVector; 

    class EntityManager {

        typedef std::vector<std::unique_ptr<System>> SystemsVector;
        typedef std::shared_ptr<BaseNode>  NodePtr;
        typedef std::function<NodePtr(Entity, SystemsVector&)> NodeFactoryFunction;

        struct NodeFactory {
            NodeFactory(ComponentMask m, NodeFactoryFunction f) :
                mask(m), create_node(f) {}

            // Mask that defines which components this node type cares about
            ComponentMask mask;

            // We store a std::function rather than making this a template
            // class as otherwise we couldn't create the NodeFactories vector
            // - we'd have to have some other way to create the nodes
            NodeFactoryFunction create_node;
        };

        typedef std::vector<NodeFactory> NodeFactories;

        public:

            // This tells entity manager about a node. This allows us to create
            // and remove nodes automatically based on the presence of
            // combinations of components.
            //
            // @see Node::get_group_ids() for how a node tells us what
            // components it cares about
            // @see self::add_component() for where a node is created
            template <typename T1>
            static void register_node(); 


            // Generate a new entity ID to use. Will re-use old ID's from
            // deleted entities if avaialable
            EntityID generate_entity_id();


            // Create a new Entity. This just holds an Entity ID and provides
            // some helper functions. When the object is destroyed the
            // underlying entity (ie. the entity ID) will still exist. Just
            // here for convenience.
            Entity create_entity();


            // Create instance of an Entity using a custom Entity class. Note
            // that this dynamically allocates storage for it.
            // TODO: Think about if you really want this kind of behaviour
            template <typename EntityType>
            std::shared_ptr<EntityType> create_entity() {
                return std::shared_ptr<EntityType>(
                        new EntityType(this, generate_entity_id()));
            }


            // TODO: Remove entity
            
            void remove_entity(EntityID entity_id) {

                // Remove nodes first as the system may do cleanup on
                // components (eg. physics system needs to cleanup bodies with
                // box2d)
                for (auto node : nodes_[entity_id]) {
                    for (auto& system : systems_) {
                        system->remove_node(node.get());
                    }
                }

                for (unsigned long i = 0 ; i < component_masks_[entity_id].size();i++) {
                    // TODO: Component removal needs to be separate as we need
                    // to be able to do it without removing the whole entity
                    if (component_masks_[entity_id].test(i)) {
                        components_[i][entity_id].reset();
                    }
                }

                nodes_[entity_id].clear(); 
                component_masks_[entity_id] = 0;

                free_ids_.push_back(entity_id);
            }


            // Add a component to an entity, optionally passing through
            // arguments to the components
            //
            // @param entity_id 
            // @param Args... arguments to pass to component
            template <typename ComponentType, typename ... Args>
            ComponentType* add_component(const EntityID entity_id, Args && ... args); 


            // Get a single component for an entity and return a pointer to it
            //
            // Returns nullptr if entity does not have requested component
            template <typename T>
            T* get_component(const EntityID entity_id);


            // Get all specific components for an entity
            //
            // Components pointers are assigned to the provided pointer ref
            // arguments.
            //
            // Note that each pointer will be set if the entity has that
            // component even if the entity doesn't have ALL components. In
            // this way you can use the return value (bool) to detect if it has
            // all components but still use available components if necessary.
            template <typename T, typename ... Ts>
            bool get_components(const EntityID entity_id, T* &first, Ts*&... rest) {
                auto mask = create_component_mask<T, Ts...>(entity_id, first, rest...);
                return (mask == (component_masks_[entity_id] & mask));
            }


            ///////////////////////////////////////////////////////////////////

            void init_component(const unsigned int&, BaseComponent*);

            // Create a system. Each system will be processed every frame by
            // self::process()
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
            
            // Called every frame
            void process(sf::RenderWindow *window);     

        private:

            // Each system controls interactions for certain nodes.
            SystemsVector systems_;

            // Component mask for an entity - indexed by entity ID
            std::vector<ComponentMask> component_masks_;

            // Nested vector; component ID indexes into vector indexed by
            // entity ID
            std::vector<std::vector<std::shared_ptr<BaseComponent>>> components_;

            // All nodes created indexed by entity id
            std::vector<std::vector<NodePtr>> nodes_; 

            // Next entity to use
            std::atomic<EntityID> next_entity_id_;

            std::list<EntityID> free_ids_;

            // TODO: Track free'd entity id's


            // Track node registrations. Nodes register themselves by calling
            // EntityManager::register_node
            static NodeFactories node_factories;

            // Generate component mask AND set component_ptr to matching
            // pointer (if any). We are mixing concerns a little bit here. What
            // we want to do is generate a mask that represents a list of
            // components. We use this to test against a entity to see if it
            // has all the components. We then need a way to get all the
            // relevant components for that entity - so we just do it as we go
            // and assign it to a pointer.
            //
            // @param entity_id this is used to determine whether we set
            // component_ptr or not.
            // @param component_ptr pointer to a component - will be set if
            // entity has this component
            //
            // @return ComponentMask
            template <typename T>
            ComponentMask create_component_mask(
                    const EntityID entity_id, T* &component_ptr);


            // We recursively reduce until we have a single template argument
            // which is handled above.
            //
            // @see create_component_mask() above
            template <typename T1, typename T2, typename ... Ts>
            ComponentMask create_component_mask(
                    const EntityID entity_id, T1* &first, T2* &second, Ts*&... rest);


    };
}

// Implementations for template functions
#include "entitymanager.ipp"
