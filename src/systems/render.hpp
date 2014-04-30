#pragma once

#include "../system.hpp"
#include "../nodes/rendernode.hpp"
#include <set>

namespace rh {

    class RenderSystem : public System {

        public:
            using System::System;
            void process(sf::RenderWindow *window);

            std::set<RenderNode*> render_nodes;

            void add_node(BaseNode *node) {
                auto n = dynamic_cast<RenderNode*>(node);
                if (n) {
                    render_nodes.insert(n);
                }
            }

            void remove_node(BaseNode *node) {
                auto n = dynamic_cast<RenderNode*>(node);
                if (n) {
                    render_nodes.erase(n);
                }
            }

    };

}
