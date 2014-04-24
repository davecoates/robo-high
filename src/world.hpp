#pragma once

#include <Box2D/Box2D.h>

#include "entity.hpp"


namespace rh {


    /**
     * This represents our physics world
     *
     * TODO: Seems clunky... think about it.
     */
    class World {
        private:
            static  std::unique_ptr<World> instance_;

            b2World world_;
        public:
            virtual         ~World() {}
            static World    *get_instance();
            b2Body*         create_body(const b2BodyDef &body_def);
            void            step();

            void            set_debug_draw(b2Draw &d);

        protected:
            World();
    };

}
