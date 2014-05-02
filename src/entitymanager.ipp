// This is because we have forward declared Entity above. We need full
// implementation for template functions below
#include "entity.hpp"
#include <cassert>

namespace rh {

    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    ComponentMask EntityManager::create_component_mask(
            const EntityID entity_id, T* &component_ptr) 
    {
        auto group_id = Component<T>::get_group_id();
        ComponentMask mask = 1 << group_id;
        if (mask == (mask & component_masks_[entity_id])) {
            component_ptr = dynamic_cast<T*>(components_[group_id][entity_id].get());
        }
        return mask;
    }

    template <typename T1, typename T2, typename ... Ts>
    ComponentMask EntityManager::create_component_mask(
            const EntityID entity_id, T1* &first, T2* &second, Ts*&... rest) 
    {
        return create_component_mask<T1>(entity_id, first) | 
            create_component_mask<T2, Ts...>(entity_id, second, rest...);
    }


    ///////////////////////////////////////////////////////////////////////////
    template <typename ComponentType, typename ... Args>
    ComponentType* EntityManager::add_component(const EntityID entity_id, Args && ... args) {

        if (entity_id >= next_entity_id_) {
            throw std::runtime_error("Can't add component to invalid entity id");
        }

        // Intantiate the new component and make sure our components_ vector
        // can accommodate it
        auto component = std::shared_ptr<ComponentType>(
                new ComponentType(std::forward<Args>(args) ...));
        auto group_id = component->get_group_id();
        if (components_.size() <= group_id) {
            components_.resize(group_id + 1);
        }
        if (components_[group_id].size() <= entity_id) {
            components_[group_id].resize(entity_id+1);
        }
        components_[group_id][entity_id] = component;

        // Update our entity component mask
        component_masks_[entity_id] |= 1 << group_id;

        // Let our systems do something with the component if necessary
        // (eg. physics system is a 3rd party library... we need access to it
        // to create necessary physics objects)
        init_component(entity_id, component.get());

        // Make sure there's room for this node
        if (nodes_.size() <= entity_id) {
            nodes_.resize(entity_id+1);
        }

        for (auto factory : node_factories) {
            // Ensure entity has required components for this node type
            if (factory.mask == (factory.mask & component_masks_[entity_id])) {
                auto node = factory.create_node(
                        Entity(this, entity_id), systems_);
                node->init();
                nodes_[entity_id].push_back(node);
            }
        }

        return component.get();
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename ComponentType>
    void EntityManager::remove_component(const EntityID entity_id) {
        auto group_id = Component<ComponentType>::get_group_id();

        assert(components_.size() > group_id);
        assert(components_[group_id].size() > entity_id);

        // Destroy any nodes that use this component first
        ComponentMask mask = 1 << group_id;
        for (auto node : nodes_[entity_id]) {
            if (mask == (node->get_component_mask() & mask)) {
                for (auto& system : systems_) {
                    system->remove_node(node.get());
                }
            }
        }

        components_[group_id][entity_id].reset();
    }


    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    T* EntityManager::get_component(const EntityID entity_id) {
        auto group_id = Component<T>::get_group_id();

        if (!component_masks_[entity_id].test(group_id)) {
            return nullptr;
        }

        return static_cast<T*>(components_[group_id][entity_id].get());
    }


    ///////////////////////////////////////////////////////////////////////////
    template <typename T1>
    void EntityManager::register_node() {
        // Create our factory function for this node type
        auto create_node = [] (Entity entity, SystemsVector &systems) {
            auto node = NodePtr(new T1(entity));
            for (auto& system : systems) {
                system->add_node(node.get());
            }
            return node;
        };
        node_factories.push_back(NodeFactory(T1::get_mask(), create_node));
    }

}
