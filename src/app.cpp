#include <typeinfo>
#include <iostream>

#include "box2d_debug.hpp"
#include "app.hpp"
#include "constants.hpp"
#include "components/renderable.hpp"
#include "components/transformable.hpp"
#include "components/physics.hpp"
#include "robo.hpp"
#include "entitymanager.hpp"

#include "systems/render.hpp"
#include "systems/physics.hpp"

using namespace std;

namespace rh {

    ///////////////////////////////////////////////////////////////////////////
    void Application::init(const string title, uint width, uint height, uint depth, bool fullscreen) 
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        auto style = sf::Style::Default;
        if (fullscreen) {
            style = sf::Style::Fullscreen;
        }
        sf::VideoMode vm(width, height, depth);
        window_ = std::unique_ptr<sf::RenderWindow>(
                new sf::RenderWindow(vm, title, style, settings));
        window_->setFramerateLimit(60);
    }

    ///////////////////////////////////////////////////////////////////////////
    void Application::run()
    {
        sf::View view;
        sf::FloatRect viewRect(0, 0, 100, 100 * rh::SCREEN_RESOLUTION_RATIO);
        view.reset(viewRect);
        window_->setView(view);

        auto em = std::unique_ptr<EntityManager>(new EntityManager());
        auto physics_system = em->create_system<PhysicsSystem>();
        em->create_system<RenderSystem>();

        auto robo = em->create_entity<Robo>();

        auto circle = em->create_entity();
        auto circle_id = circle.id();
        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(1.0f, 1.f);
        BodyDef.type = b2_dynamicBody;
        //auto* body = physics_system->create_body(BodyDef);
        //body->SetUserData(&circle_id);

        b2CircleShape Shape;
        Shape.m_p.Set(1.0f, 1.0f);
        Shape.m_radius = 1.0f;
        b2FixtureDef FixtureDef;
        FixtureDef.density = 1.f;
        FixtureDef.friction = 0.7f;
        FixtureDef.shape = &Shape;
        FixtureDef.restitution = 0.5f;
        //body->CreateFixture(&FixtureDef);


        auto shape = new sf::CircleShape(1.0f);
        shape->setFillColor(sf::Color::Red);
        circle.add_component<rh::components::Renderable>(shape);
        //em->add_component<rh::components::Renderable>(circle_id, shape);
        em->add_component<rh::components::Transformable>(circle_id, shape);
        em->add_component<rh::components::Physics>(circle_id, BodyDef, FixtureDef);
        //

        // Create the ground
        //
        auto ground_id = em->generate_entity_id();
        auto ground_shape = new sf::RectangleShape(sf::Vector2f(20.f, 2.f));
        ground_shape->setOrigin(10, 1.f);
        ground_shape->setFillColor(sf::Color::Green);
        em->add_component<rh::components::Transformable>(ground_id, ground_shape);
        em->add_component<rh::components::Renderable>(ground_id, ground_shape);

        b2BodyDef body_def;
        body_def.position = b2Vec2(0.f, 10.f);
        body_def.type = b2_staticBody;
        body_def.angle = b2_pi / 180 * 10;
        //auto* ground = physics_system->create_body(body_def);
        //ground->SetUserData(&ground_id);

        b2PolygonShape ground_shape2;
        ground_shape2.SetAsBox(20.f/2,2.f/2);
        b2FixtureDef ground_fixture;
        ground_fixture.density = 0.f;
        ground_fixture.shape = &ground_shape2;
        //ground->CreateFixture(&ground_fixture);

        em->add_component<rh::components::Physics>(ground_id, body_def, ground_fixture);

        Box2dDebugDraw debug(window_.get());
        physics_system->set_debug_draw(debug);

        //
        sf::Clock clock;

        while (window_->isOpen())
        {
            sf::Event event;
            while (window_->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window_->close();
                if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                        case  sf::Keyboard::Escape:
                            window_->close();
                            break;
                        default:
                            break;
                    }
                }

            }

            robo->update(clock.getElapsedTime());

            window_->clear(sf::Color::White);

            //physics_system->process(window_);
            //render_system->process(window_);
            em->process(window_.get());
            window_->display();
        }

    }


}
