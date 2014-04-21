#include "app.hpp"
#include "constants.hpp"
#include "components/renderable.hpp"
#include "robo.hpp"
#include <typeinfo>
#include "entitymanager.hpp"
#include <iostream>
#include <Box2D/Box2D.h>

using namespace std;

namespace RH {

    // Convert b/w world and pixel coordinates
    static const float SCALE = 30.f;

    b2Body* CreateGround(b2World& World, float X, float Y)
    {
        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
        BodyDef.type = b2_staticBody;
        b2Body* Body = World.CreateBody(&BodyDef);

        b2PolygonShape Shape;
        Shape.SetAsBox((800.f/2)/SCALE, (16.f/2)/SCALE);
        b2FixtureDef FixtureDef;
        FixtureDef.density = 0.f;
        FixtureDef.shape = &Shape;
        Body->CreateFixture(&FixtureDef);

        return Body;
    }


void CreateBox(b2World& World, int MouseX, int MouseY)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(MouseX/SCALE, MouseY/SCALE);
    BodyDef.type = b2_dynamicBody;
    b2Body* Body = World.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((32.f/2)/SCALE, (32.f/2)/SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.f;
    FixtureDef.friction = 0.7f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
}


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



        b2Vec2 Gravity(0.f, 9.8f);
        b2World World(Gravity);
        auto ground = CreateGround(World, 400.f, 500.f);

        sf::Clock clock;

        sf::Texture GroundTexture;
        sf::Texture BoxTexture;
        GroundTexture.loadFromFile("../resources/ground.png");
        BoxTexture.loadFromFile("../resources/box.png");

        std::cout << "Position: " << Component<RHComponents::Renderable>::get_group_id() << std::endl;

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

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                int MouseX = sf::Mouse::getPosition(*window_).x;
                int MouseY = sf::Mouse::getPosition(*window_).y;
                CreateBox(World, MouseX, MouseY);
            }

            World.Step(1/60.f, 8, 3);

            ////

            World.Step(1/60.f, 8, 3);

            window_->clear(sf::Color::White);
            int BodyCount = 0;
            for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
            {
                if (BodyIterator->GetType() == b2_dynamicBody)
                {
                    sf::Sprite Sprite;
                    Sprite.setTexture(BoxTexture);
                    Sprite.setOrigin(16.f, 16.f);
                    Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
                    Sprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
                    window_->draw(Sprite);
                    ++BodyCount;
                }
                else
                {
                }
            }

                    sf::Sprite GroundSprite;
                    GroundSprite.setTexture(GroundTexture);
                    GroundSprite.setOrigin(400.f, 8.f);
                    GroundSprite.setPosition(ground->GetPosition().x * SCALE, ground->GetPosition().y * SCALE);
                    GroundSprite.setRotation(180/b2_pi * ground->GetAngle());
                    window_->draw(GroundSprite);


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
