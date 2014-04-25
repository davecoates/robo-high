#include <typeinfo>
#include <iostream>

#include "box2d_debug.hpp"
#include "app.hpp"
#include "constants.hpp"
#include "components/renderable.hpp"
#include "components/transformable.hpp"
#include "components/physics.hpp"
#include "robo.hpp"
#include "world.hpp"
#include "entitymanager.hpp"

using namespace std;

namespace rh {

    std::unique_ptr<Application> Application::instance_;

    ///////////////////////////////////////////////////////////////////////////
    Application *Application::get_instance() {
        if (!instance_) {
            instance_.reset(new Application());
        }
        return instance_.get();
    }

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
        window_ = new sf::RenderWindow(vm, title, style, settings);
        window_->setFramerateLimit(60);
    }

    ///////////////////////////////////////////////////////////////////////////
    void Application::run()
    {
        sf::View view;
        sf::FloatRect viewRect(0, 0, 100, 100 * rh::SCREEN_RESOLUTION_RATIO);
        view.reset(viewRect);
        window_->setView(view);

        auto em = EntityManager::get_instance();
        std::cout << em->generate_entity() << "#\n";
        std::cout << em->generate_entity() << "#\n";

        auto world = World::get_instance();

        auto robo_id = em->generate_entity();
        auto robo = new Robo(robo_id);



        auto circle_id = em->generate_entity();
        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(1.0f, 1.f);
        BodyDef.type = b2_dynamicBody;
        auto* body = world->create_body(BodyDef);
        body->SetUserData(&circle_id);

        b2CircleShape Shape;
        Shape.m_p.Set(1.0f, 1.0f);
        Shape.m_radius = 1.0f;
        b2FixtureDef FixtureDef;
        FixtureDef.density = 1.f;
        FixtureDef.friction = 0.7f;
        FixtureDef.shape = &Shape;
        FixtureDef.restitution = 0.5f;
        body->CreateFixture(&FixtureDef);


        auto shape = new sf::CircleShape(1.0f);
        shape->setFillColor(sf::Color::Red);
        em->add_component<rh::components::Renderable>(circle_id, shape);
        em->add_component<rh::components::Transformable>(circle_id, shape);
        em->add_component<rh::components::Physics>(circle_id);
        //

        // Create the ground
        //
        auto ground_id = em->generate_entity();
        auto ground_shape = new sf::RectangleShape(sf::Vector2f(20.f, 2.f));
        ground_shape->setOrigin(10, 1.f);
        ground_shape->setFillColor(sf::Color::Green);
        em->add_component<rh::components::Transformable>(ground_id, ground_shape);
        em->add_component<rh::components::Renderable>(ground_id, ground_shape);
        em->add_component<rh::components::Physics>(ground_id);

        b2BodyDef body_def;
        body_def.position = b2Vec2(0.f, 10.f);
        body_def.type = b2_staticBody;
        body_def.angle = b2_pi / 180 * 10;
        auto* ground = world->create_body(body_def);
        ground->SetUserData(&ground_id);

        b2PolygonShape ground_shape2;
        ground_shape2.SetAsBox(20.f/2,2.f/2);
        b2FixtureDef ground_fixture;
        ground_fixture.density = 0.f;
        ground_fixture.shape = &ground_shape2;
        ground->CreateFixture(&ground_fixture);

        Box2dDebugDraw debug(window_);
        world->set_debug_draw(debug);

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

            world->step();

            for (auto entity_id : em->get_entities()) {
                rh::components::Transformable *p1 = nullptr;
                rh::components::Renderable *p3 = nullptr;

                em->get_components<rh::components::Transformable, rh::components::Renderable>(entity_id, p1, p3);
                if (p3) {
                    window_->draw(*p3->drawable);
                }
            }

            std::cout << '\n';

            window_->display();
        }

    }


}
