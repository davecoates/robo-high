#include "entitymanager.hpp"

namespace RH {

    std::unique_ptr<EntityManager> EntityManager::instance_;

    ///////////////////////////////////////////////////////////////////////////
    EntityManager *EntityManager::get_instance() {
        if (!instance_) {
            instance_.reset(new EntityManager());
        }
        return instance_.get();
    }

}
