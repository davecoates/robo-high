#include "world.hpp"
#include "components/position.hpp"
#include "entitymanager.hpp"
#include <iostream>

namespace RH {


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
            auto entity = (RH::EntityID*)it->GetUserData();
            auto position = em->get_component<RHComponents::Position>(*entity);
            if (position) {
                auto new_pos = it->GetPosition();
                position->x = new_pos.x;
                position->y = new_pos.y;
                if (position->transformable) {
                    position->transformable->setPosition(position->x, position->y);
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
