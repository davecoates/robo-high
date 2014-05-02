#pragma once

#include <SFML/Graphics.hpp>
#include <Box2d/Box2D.h>
#include "entity.hpp"

namespace rh {

    class EntityManager;

    class Robo : public sf::Drawable,  public sf::Transformable, public Entity {
        private:
            sf::RectangleShape shape_;
            sf::CircleShape circle;
            sf::Texture texture;
            //sf::Shader shader;

            virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;

        public:
            Robo(EntityManager* em, EntityID entity_id);

            void update(const sf::Time &t);

    };

}
