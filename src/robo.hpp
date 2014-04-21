#pragma once

#include <SFML/Graphics.hpp>
#include "entity.hpp"

namespace RH {

    class Robo : public Entity, public sf::Drawable,  public sf::Transformable {
        private:
            sf::RectangleShape shape;
            sf::CircleShape circle;
            sf::Texture texture;
            sf::Shader shader;


            virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;

        public:
            Robo();

            void update(const sf::Time &t);

    };

}
