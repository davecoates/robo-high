#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "robo.hpp"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::VideoMode vm(RH::SCREEN_RESOLUTION_W, RH::SCREEN_RESOLUTION_H);
    sf::RenderWindow window(vm, "SFML works!", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::View view;
    sf::FloatRect viewRect(0, 0, 200, 200 * RH::SCREEN_RESOLUTION_RATIO);
    view.reset(viewRect);
    window.setView(view);


    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    std::vector<std::shared_ptr<RH::Entity>> renderables;
    RH::Robo *robo = new RH::Robo();
    robo->setPosition(20.0f, 15.f);
    renderables.push_back(std::shared_ptr<RH::Entity>(robo));

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case  sf::Keyboard::Escape:
                        window.close();
                        break;
                    default:
                        break;
                }
            }

        }

        window.clear();

        for (auto renderable : renderables) {
            renderable->update(clock.getElapsedTime());
            window.draw(*renderable);
        }

        window.display();
    }

    return 0;
}
