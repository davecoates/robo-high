#include "box2d_debug.hpp"
#include <iostream>

namespace rh {

    sf::Color convert_color(const b2Color &c) {
        return sf::Color(
                static_cast<sf::Uint8>(c.r*255),
                static_cast<sf::Uint8>(c.g*255),
                static_cast<sf::Uint8>(c.b*255));
    }

    sf::ConvexShape Box2dDebugDraw::create_polygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
        sf::ConvexShape polygon(vertexCount);
        for(int i = 0; i < vertexCount; i++) {
            sf::Vector2f v(vertices[i].x*scale_, vertices[i].y*scale_);
            polygon.setPoint(i, v);
        }
        polygon.setOutlineThickness(-1.f);
        auto c = convert_color(color);
        polygon.setFillColor(c);
        polygon.setOutlineColor(c);
        return polygon;
    }

    void Box2dDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
        auto polygon = create_polygon(vertices, vertexCount, color);
        polygon.setFillColor(sf::Color::Transparent);
        window_->draw(polygon);
    }

    void Box2dDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
        auto polygon = create_polygon(vertices, vertexCount, color);
        window_->draw(polygon);
    }

    void Box2dDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
        sf::CircleShape circle(radius * scale_);
        circle.setOrigin(radius * scale_, radius * scale_);
        circle.setPosition(sf::Vector2f(center.x*scale_, center.y*scale_));
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineThickness(-1.f);
        circle.setOutlineColor(convert_color(color));

        window_->draw(circle);
    }

    void Box2dDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2&, const b2Color& color) {
        // What should this actually draw? What is axis for?
        sf::CircleShape circle(radius * scale_);
        circle.setOrigin(radius * scale_, radius * scale_);
        circle.setPosition(sf::Vector2f(center.x*scale_, center.y*scale_));
        auto c = convert_color(color);
        circle.setFillColor(c);
        circle.setOutlineThickness(-1.f);
        circle.setOutlineColor(c);

        window_->draw(circle);
    }

    void Box2dDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
        auto c = convert_color(color);
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(p1.x * scale_, p1.y * scale_), c),
            sf::Vertex(sf::Vector2f(p2.x * scale_, p2.y * scale_), c)
        };

        window_->draw(line, 2, sf::Lines);
    }

    void Box2dDebugDraw::DrawTransform(const b2Transform& xf) {

        b2Vec2 xAxis = xf.p +  xf.q.GetXAxis();
        sf::Vertex x_line[] = 
        {
            sf::Vertex(sf::Vector2f(xf.p.x*scale_, xf.p.y*scale_), sf::Color::Red),
            sf::Vertex(sf::Vector2f(xAxis.x*scale_, xAxis.y*scale_), sf::Color::Red)
        };
        window_->draw(x_line, 2, sf::Lines);

        b2Vec2 yAxis = xf.p +  xf.q.GetYAxis();
        sf::Vertex y_line[] = 
        {
            sf::Vertex(sf::Vector2f(xf.p.x*scale_, xf.p.y*scale_), sf::Color::Green),
            sf::Vertex(sf::Vector2f(yAxis.x*scale_, yAxis.y*scale_), sf::Color::Green)
        };

        window_->draw(y_line, 2, sf::Lines);
    }
}
