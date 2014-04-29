#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "app.hpp"
#include <iostream>

#include "node.hpp"

int main()
{
    auto app = std::unique_ptr<rh::Application>(new rh::Application());

    app->init("Robo High", rh::SCREEN_RESOLUTION_W, rh::SCREEN_RESOLUTION_H, 32, false);
    app->run();

    auto rn = new rh::RenderNode();
    auto pn = new rh::PhysicsNode();

    std::cout << rh::RenderNode::get_mask() << std::endl;
    std::cout << rh::PhysicsNode::get_mask() << std::endl;
    std::cout << rh::PositionNode::get_mask() << std::endl;
    std::cout << "Render Node: " << rn->get_mask() << std::endl;
    std::cout << "Physics Node: " << pn->get_mask() << std::endl;
    return 0;
}
