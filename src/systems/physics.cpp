#include "physics.hpp"
#include "../contactlistener.hpp"

namespace rh {


    void PhysicsSystem::init() {
        world_ = std::unique_ptr<b2World>(new b2World(b2Vec2(0.f, 9.8f)));
        contact_listener_ = std::unique_ptr<ContactListener>(new ContactListener(physics_nodes_));
        world_->SetContactListener(contact_listener_.get());
    }

    b2Body* PhysicsSystem::create_body(const b2BodyDef &body_def) {
        return world_->CreateBody(&body_def);
    }

    void PhysicsSystem::process(sf::RenderWindow *) {
        world_->Step(1/60.f, 8, 3);

        for (b2Body* it = world_->GetBodyList(); it; it = it->GetNext()) {
            auto entity = (rh::EntityID*)it->GetUserData();
            if (physics_nodes_.find(*entity) != physics_nodes_.end()) {
                auto& t_comp = physics_nodes_[*entity]->transformable_;
                auto new_pos = it->GetPosition();
                if (t_comp->transformable) {
                    t_comp->transformable->setPosition(new_pos.x, new_pos.y);
                    t_comp->transformable->setRotation(it->GetAngle() * 180.f/b2_pi);
                }
            }
        }

        world_->DrawDebugData();
    }

    void PhysicsSystem::set_debug_draw(b2Draw &d) {
        world_->SetDebugDraw(&d);
        d.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
    }

    void PhysicsSystem::init_component(const unsigned int &entity_id, BaseComponent* component) {

        // TODO: This seems bad.. is there a better way?
        auto c = dynamic_cast<components::Physics*>(component);
        if (c) {
            c->entity_id = entity_id;
            c->body = world_->CreateBody(&c->body_def);
            c->body->SetUserData(&c->entity_id);

            for (auto& fixture : c->fixtures) {
                c->body->CreateFixture(&fixture);
            }

        }
    }


}
