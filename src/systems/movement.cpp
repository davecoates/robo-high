#include "movement.hpp"
#include "../components/movement.hpp"
#include "../components/physics.hpp"
#include "../components/contactsensor.hpp"
#include <vector>
#include <stdexcept>
#include <iostream>

namespace rh {


    void MovementSystem::process(sf::RenderWindow*) {
        // Generate list of movement 'intents'
        // TODO: This will need to change. It would be nice to be able to have
        // these not to be tied to keyboard events - eg. AI could generate
        // intents instead
        std::vector<MovementIntent> intents;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            intents.push_back(MovementIntent::MoveForward);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            intents.push_back(MovementIntent::MoveBackward);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            intents.push_back(MovementIntent::Jump);
        }

        // Apply each intent to entities with relevant components
        for (auto node : nodes_) {
            auto movement = node->movement_;
            auto p = node->physics_;
            //auto has_both = entity.get_components<rh::components::Movement, rh::components::Physics>(movement, p);

            auto* sensor = node->get_entity().get_component<rh::components::ContactSensor>();

            if (intents.size() > 0) {
                b2Vec2 current_velocity = p->body->GetLinearVelocity();
                auto mass = p->body->GetMass();
                // Accumulate desired changes into a single impulse
                b2Vec2 impulse(0.f, 0.f);
                for (auto& intent : intents) {
                    auto desired_velocity = 0.f;
                    auto apply_change = true, is_vertical = false;

                    switch (intent) {
                        case MovementIntent::MoveBackward:
                            desired_velocity = -movement->horizontal_speed;
                            break;
                        case MovementIntent::None:
                            apply_change = false;
                            break;
                        case MovementIntent::MoveForward:
                            desired_velocity = movement->horizontal_speed;
                            break;
                        case MovementIntent::Jump:
                            // Only jump if in contact with something
                            // TODO: This currently assumes you can only be contact
                            // with something you could jump off
                            if (sensor && sensor->fixtures_in_contact.size()) {
                                is_vertical = true;
                                desired_velocity = -movement->vertical_speed;
                            } else {
                                apply_change = false;
                            }
                            break;
                    }

                    if (apply_change) {
                        auto change = desired_velocity - 
                            (is_vertical ? current_velocity.y : current_velocity.x);
                        if (is_vertical) {
                            impulse.y += mass * change;
                        } else {
                            impulse.x += mass * change;
                        }
                    }
                }

                p->body->ApplyLinearImpulse(impulse, p->body->GetWorldCenter(), true);
            }
        }
    }

}
