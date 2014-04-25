#pragma once

#include <SFML/Graphics.hpp>
#include <Box2d/Box2D.h>
#include "entitymanager.hpp"

namespace rh {

    class Robo : public sf::Drawable,  public sf::Transformable {
        private:
            sf::RectangleShape shape_;
            sf::CircleShape circle;
            sf::Texture texture;
            sf::Shader shader;

            // TODO: Maybe I should go back to extending a base Entity class
            // rather than tracking entity_id?
            EntityID entity_id_;

            b2Body* body_;

            virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;

        public:
            Robo(EntityID entity_id);

            void update(const sf::Time &t);

    };

}
