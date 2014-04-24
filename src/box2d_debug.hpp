#pragma once
#include <Box2d/Box2D.h>
#include <SFML/Graphics.hpp>

namespace rh {

    class Box2dDebugDraw : public b2Draw
    {
        private:
            sf::ConvexShape create_polygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
            sf::RenderWindow* window_;
            float scale_;
        public:
            Box2dDebugDraw(sf::RenderWindow *window, float scale = 1.f) : window_(window), scale_(scale) {}

            void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

            void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

            void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

            void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

            void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

            void DrawTransform(const b2Transform& xf);
    };
}
