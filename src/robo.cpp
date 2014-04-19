#include <SFML/Graphics.hpp>
#include "robo.hpp"
#include <math.h>
#include <iostream>

namespace RH {

    void Robo::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        auto transform = this->getTransform();
        states.shader = &shader;
        states.transform = transform;
        target.draw(shape, states);
        target.draw(circle, states);
    }

    Robo::Robo() {
        sf::Vector2f size(10.f, 10.f);
        shape.setFillColor(sf::Color::Green);
        shape.setSize(size);
        //shape.setOutlineThickness(1.f);
        //shape.setOutlineColor(sf::Color::Magenta);
        shape.setPosition(0.f, 10.f);

        if (!texture.loadFromFile("../resources/test.png")) {
            throw std::runtime_error("Couldn't load texture");
        }
        shape.setTexture(&texture);

        if (!shader.loadFromFile("../resources/pixelate.frag", sf::Shader::Fragment)) {
            throw std::runtime_error("Couldn't load shader");
        }
        shader.setParameter("texture", sf::Shader::CurrentTexture);
        circle.setTexture(&texture);

        circle.setRadius(5.f);
        //circle.setFillColor(sf::Color::Red);
        circle.setOrigin(5.f, 5.f);
        //circle.setOutlineThickness(1.f);
        //circle.setOutlineColor(sf::Color::Magenta);
    }

    void Robo::update(const sf::Time &t) {
        shader.setParameter("blur_radius", 0.03f);
        circle.setRotation(t.asSeconds()*1000);
    }

}
