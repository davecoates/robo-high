#include "contactlistener.hpp"

#include <iostream>

namespace rh {

    // When contact begins we want to update the associated entities
    // ContactSensor component (if present) and ADD that fixture it came in
    // contact with.
    void ContactListener::BeginContact(b2Contact* contact) {
        auto insert = [this, contact] (b2Fixture* fixture) {
            auto id = (rh::EntityID*)(fixture->GetUserData());
            if (id) {
                auto sensor = physics_nodes_[*id]->get_entity().get_component<rh::components::ContactSensor>();
                if (sensor) {
                    sensor->fixtures_in_contact.insert(fixture);
                }
            }
        };

        insert(contact->GetFixtureA());
        insert(contact->GetFixtureB());
    }

    // When contact ends we want to update the associated entities
    // ContactSensor component (if present) and REMOVE that fixture it came in
    // contact with.
    void ContactListener::EndContact(b2Contact* contact) {
        auto erase = [this, contact] (b2Fixture* fixture) {
            auto id = static_cast<rh::EntityID*>(fixture->GetUserData());
            if (id) {
                auto sensor = physics_nodes_[*id]->get_entity().get_component<rh::components::ContactSensor>();
                if (sensor) {
                    sensor->fixtures_in_contact.erase(fixture);
                }

            }
        };

        erase(contact->GetFixtureA());
        erase(contact->GetFixtureB());
    }
}
