#pragma once

#include <Box2D/Box2D.h>

#include "../system.hpp"
#include "../components.hpp"

#include "../contactlistener.hpp"

namespace rh {

    class PhysicsSystem : public System {

        private:
            std::unique_ptr<b2World> world_;
            //std::unique_ptr<ContactListener> contact_listener_;

        public:
            using System::System;

            void            init();
            b2Body*         create_body(const b2BodyDef &body_def);
            void            process(sf::RenderWindow *window);

            void            set_debug_draw(b2Draw &d);

            void            init_component(const unsigned int &entity_id, BaseComponent* component);

    };

}
