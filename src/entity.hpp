#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <typeinfo>
#include  "component.hpp"

namespace RH {

    class Entity 
    {
        typedef std::vector<std::vector<std::shared_ptr<BaseComponent>>> ComponentsVector;
        protected:
            ComponentsVector components_;

        public:
            template <typename T>
            T* add_component() {
                auto ptr = std::shared_ptr<T>(new T());
                auto group_id = ptr->get_group_id();
                std::cout << group_id << '\n';
                if (components_.size() <= group_id) {
                    components_.resize(group_id + 1);
                }
                components_[ptr.get()->get_group_id()].push_back(ptr);
                return ptr.get();
            }

            // TODO: This was just test of concept. Need to be able to get
            // entities that have all specified components
            // eg. get_components<Position,Movement>()
            template <typename T>
            const std::vector<std::shared_ptr<T>> get_components() {
                auto components = std::vector<std::shared_ptr<T>>();
                auto group_id = Component<T>::get_group_id();
                for (auto it : components_[group_id]) {
                    std::shared_ptr<T> i(std::dynamic_pointer_cast<T>(it));
                    components.push_back(i);
                }
                return components;
            }



    };

}
