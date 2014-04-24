#include "world.hpp"
#include "components/transformable.hpp"
#include "components/physics.hpp"
#include "entitymanager.hpp"
#include <iostream>

namespace rh {


    std::unique_ptr<World> World::instance_;

    ///////////////////////////////////////////////////////////////////////////
    World *World::get_instance() {
        if (!instance_) {
            instance_.reset(new World());
        }
        return instance_.get();
    }

    World::World() : world_(b2Vec2(0.f, 9.8f)) { }

    b2Body* World::create_body(const b2BodyDef &body_def) {
        return world_.CreateBody(&body_def);
    }

    void World::step() {
        world_.Step(1/60.f, 8, 3);

        auto em = EntityManager::get_instance();

        for (b2Body* it = world_.GetBodyList(); it; it = it->GetNext()) {
            auto entity = (rh::EntityID*)it->GetUserData();
            rh::components::Physics* _ = nullptr;
            rh::components::Transformable* position = nullptr;
            auto has_all = em->get_components<rh::components::Physics, rh::components::Transformable>(*entity, _, position);
            if (has_all) {
                auto new_pos = it->GetPosition();
                if (position->transformable) {
                    position->transformable->setPosition(new_pos.x, new_pos.y);
                    position->transformable->setRotation(it->GetAngle() * 180.f/b2_pi);
                }
            }
        }

        world_.DrawDebugData();
    }

    void World::set_debug_draw(b2Draw &d) {
        world_.SetDebugDraw(&d);
        d.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
    }

}
