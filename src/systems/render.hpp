#pragma once

#include "../system.hpp"
#include <set>

namespace rh {

    class RenderSystem : public System {

        public:
            using System::System;
            void process(sf::RenderWindow *window);

            std::set<RenderNode*> render_nodes;

            void add_node(BaseNode *node) {
                std::cout << "Type: " << node->get_type() << std::endl;
                auto n = dynamic_cast<RenderNode*>(node);
                if (n) {
                    render_nodes.insert(n);
                }
            }
    };

}
