#pragma once

#include <Box2D/Box2D.h>

#include "../system.hpp"
#include "../components.hpp"

namespace rh {

    class PhysicsSystem : public System {

        private:
            b2World world_;

        public:
                            PhysicsSystem();
            b2Body*         create_body(const b2BodyDef &body_def);
            void            process(sf::RenderWindow *window);

            void            set_debug_draw(b2Draw &d);

            void            init_component(const unsigned int &entity_id, BaseComponent* component);

    };

}
