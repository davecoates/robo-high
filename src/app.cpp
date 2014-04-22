#include "app.hpp"
#include "constants.hpp"
#include "components/renderable.hpp"
#include "robo.hpp"
#include <typeinfo>
#include "entitymanager.hpp"
#include <iostream>

using namespace std;

namespace RH {

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
        // I Don't understand views yet
        //sf::View view;
        //sf::FloatRect viewRect(0, 400, 200, 200 * RH::SCREEN_RESOLUTION_RATIO);
        //view.reset(viewRect);
        //window_->setView(view);

        auto em = EntityManager::get_instance();

        auto robo = em->create_entity<Robo>();

        robo->setPosition(20.0f, 15.f);

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

            // TODO: Just a test. This is basically a system - in this case the
            // render system
            for (auto renderable : em->get_entities()) {
                auto components = renderable->get_components<RHComponents::Renderable>();
                for (auto component : components) {
                    window_->draw(*component->drawable);
                }
                //renderable->update(clock.getElapsedTime());
                //window_->draw(*renderable);
            }

            window_->display();
        }

    }


}
