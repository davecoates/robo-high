#pragma once

#include <vector>

#include "entity.hpp"

namespace RH {

    class EntityManager {

        typedef std::vector<std::shared_ptr<Entity>> EntityVector;

        private:
            EntityVector entities_;
            static  std::unique_ptr<EntityManager> instance_;

        public:
            template<typename T>
            T* create_entity() {
                auto ptr = std::shared_ptr<T>(new T());
                entities_.push_back(ptr);
                return ptr.get();
            }

            static EntityManager *get_instance();

            const EntityVector& get_entities() { return entities_; }


    };
}
