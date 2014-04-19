#ifndef __ROBO_H_
#define __ROBO_H_

#include <SFML/Graphics.hpp>

namespace RH {

    class Entity : public sf::Drawable,  public sf::Transformable {
        public:
            virtual void update(const sf::Time &t) = 0;
    };

    class Robo :  public Entity {
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
#endif // __ROBO_H_
