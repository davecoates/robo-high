#include "keyboardinput.hpp"
#include "../components.hpp"
#include "../entitymanager.hpp"
#include <iostream>
#include <stdexcept>
#include <iostream>

namespace rh {

    std::vector<EntityID> entities;

    // Just for testing
    static void generate_shape(EntityManager* em, float x = 4.f, float y = 1.f) {
        auto entity = em->create_entity();
        auto shape = new sf::CircleShape(1.0f);
        shape->setFillColor(sf::Color::Red);
        shape->setOrigin(1.0f, 1.0f);

        b2BodyDef body_def;
        body_def.position = b2Vec2(x, y);
        body_def.type = b2_dynamicBody;

        b2CircleShape body_shape;
        body_shape.m_p.Set(0.0f, 0.0f);
        body_shape.m_radius = 1.0f;
        b2FixtureDef fixture;
        fixture.density = 1.f;
        fixture.friction = 0.7f;
        fixture.shape = &body_shape;
        fixture.restitution = 0.1f;


        entity.add_component<rh::components::Renderable>(shape);
        entity.add_component<rh::components::Transformable>(shape);
        entity.add_component<rh::components::Physics>(body_def, fixture);

        entities.push_back(entity.id());
    }

    void KeyboardInputSystem::process(sf::RenderWindow *window) {

        if (event_count_) {
            auto p = sf::Mouse::getPosition();
            auto window_p = window->getPosition();
            float x = p.x - window_p.x , y = p.y - window_p.y ;
            for (unsigned int i =0; i < event_count_;i++) {
                auto &key = event_pool_[i];
                switch (key.code) {
                    case  sf::Keyboard::Escape:
                        window->close();
                        break;
                    case sf::Keyboard::I:
                        // TESTING
                        generate_shape(em_, 
                                (x / rh::SCREEN_RESOLUTION_W) * 100.f,
                                (y / rh::SCREEN_RESOLUTION_H) * 100.f * rh::SCREEN_RESOLUTION_RATIO
                                );
                        break;
                    case sf::Keyboard::A:
                        em_->add_component<rh::components::Movement>(0);
                        break;
                    case sf::Keyboard::R:
                        em_->remove_component<rh::components::Movement>(0);
                        break;
                    case sf::Keyboard::D:
                        if (entities.size()) {
                            em_->remove_entity(entities.back());
                            entities.pop_back();
                        }
                    default:
                        break;
                }
            }
            event_count_ = 0;
        }
    }

    void KeyboardInputSystem::add_event(const sf::Event::KeyEvent &event) {
        if (event_count_ >= EVENT_POOL_SIZE) {
            throw std::runtime_error("Keyboard events exceed pool size");
        }
        event_pool_[event_count_].code = event.code;
        event_pool_[event_count_].alt = event.alt;
        event_pool_[event_count_].control = event.control;
        event_pool_[event_count_].shift = event.shift;
        event_pool_[event_count_].system = event.system;
        event_count_ = event_count_ + 1;
    }

}
