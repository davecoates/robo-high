#include "movement.hpp"
#include "../components/movement.hpp"
#include "../components/physics.hpp"
#include <iostream>
#include <stdexcept>
#include <iostream>

namespace rh {


    void MovementSystem::process(sf::RenderWindow *window, const EntityVector& entities) {

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

        for (auto entity : entities) {
            rh::components::Movement *_;
            rh::components::Physics *p;
            auto has_both = entity.get_components<rh::components::Movement, rh::components::Physics>(_, p);

            if (has_both) {
                b2Vec2 vel = p->body->GetLinearVelocity();
                float desiredVel = 0;
                bool is_vertical = false;
                for (auto& intent : intents) {
                    switch ( intent )
                    {
                        case MovementIntent::MoveBackward:  desiredVel = -5; break;
                        case MovementIntent::None:  desiredVel =  0; break;
                        case MovementIntent::MoveForward: desiredVel =  5; break;
                        case MovementIntent::Jump: desiredVel = -1; is_vertical = true; break;
                    }
                    float velChange = desiredVel - vel.x;
                    float impulse_c = p->body->GetMass() * velChange; 
                    b2Vec2 impulse;
                    if (is_vertical) {
                        impulse = b2Vec2(0, impulse_c);
                    } else {
                        impulse = b2Vec2(impulse_c,0);
                    }
                    p->body->ApplyLinearImpulse(impulse, p->body->GetWorldCenter(), true);
                }
            }
        }
    }

}
