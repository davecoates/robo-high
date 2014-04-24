#include "entitymanager.hpp"

namespace rh {

    std::unique_ptr<EntityManager> EntityManager::instance_;

    ///////////////////////////////////////////////////////////////////////////
    EntityManager *EntityManager::get_instance() {
        if (!instance_) {
            auto em = new EntityManager();
            em->next_entity_id_ = 0;
            instance_.reset(em);
        }
        return instance_.get();
    }

}
