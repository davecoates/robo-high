#pragma once

#include <Box2D/Box2D.h>
#include <map>

#include "../system.hpp"
#include "../components.hpp"

#include "../contactlistener.hpp"

#include "../nodes/physicsnode.hpp"

namespace rh {

    typedef std::map<EntityID, PhysicsNode*> PhysicsNodes;

    class PhysicsSystem : public System {

        private:
            std::unique_ptr<b2World> world_;
            std::unique_ptr<ContactListener> contact_listener_;

            PhysicsNodes physics_nodes_;

        public:
            using System::System;

            void            init();
            b2Body*         create_body(const b2BodyDef &body_def);
            void            process(sf::RenderWindow *window);

            void            set_debug_draw(b2Draw &d);

            void            init_component(const unsigned int &entity_id, BaseComponent* component);

            void add_node(BaseNode *node) {
                auto n = dynamic_cast<PhysicsNode*>(node);
                if (n) {
                    physics_nodes_[n->get_entity_id()] = n;
                }
            }

            void remove_node(BaseNode *node) {
                auto n = dynamic_cast<PhysicsNode*>(node);
                if (n) {
                    auto it = physics_nodes_.find(n->get_entity_id());
                    world_->DestroyBody(it->second->physics_->body);
                    physics_nodes_.erase(it);
                }
            }

    };

}
