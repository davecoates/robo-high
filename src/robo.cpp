#include <SFML/Graphics.hpp>
#include "robo.hpp"
#include "entity.hpp"
#include "components/transformable.hpp"
#include "components/renderable.hpp"
#include "components/physics.hpp"
#include "components/movement.hpp"
#include "components/contactsensor.hpp"
#include <cmath>
#include <iostream>

namespace rh {

    void Robo::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        auto transform = this->getTransform();
        //states.shader = &shader;
        states.transform = transform;
        target.draw(shape_, states);
        target.draw(circle, states);
    }

    Robo::Robo(EntityManager* em, EntityID entity_id) : Entity(em, entity_id) {
        sf::Vector2f size(1.5f, 1.5f);
        //shape_.setFillColor(sf::Color::Green);
        shape_.setSize(size);
        shape_.setOrigin(size.x/2, 1.75f);
        //shape.setOutlineThickness(1.f);
        //shape.setOutlineColor(sf::Color::Magenta);

        if (!texture.loadFromFile("../resources/wheel.png")) {
            throw std::runtime_error("Couldn't load texture");
        }
        shape_.setTexture(&texture);

        //if (!shader.loadFromFile("../resources/bloom.frag", sf::Shader::Fragment)) {
            //throw std::runtime_error("Couldn't load shader");
        //}
        //shader.setParameter("sourceTexture", sf::Shader::CurrentTexture);
        circle.setTexture(&texture);

        circle.setRadius(1.f);
        //circle.setFillColor(sf::Color::Red);
        circle.setOrigin(1.f, 1.f);
        //circle.setOutlineThickness(1.f);
        //circle.setOutlineColor(sf::Color::Magenta);

        add_component<rh::components::Renderable>(this);
        add_component<rh::components::Transformable>(this);

        add_component<rh::components::Movement>(5.0f, 5.0f);
        add_component<rh::components::ContactSensor>();

        b2BodyDef roboBodyDef;
        roboBodyDef.position = b2Vec2(4.0f, 1.f);
        //roboBodyDef.angle = b2_pi / 180 * 10;
        roboBodyDef.type = b2_dynamicBody;
        //body_ = world->create_body(roboBodyDef);
        //body_->SetUserData(&entity_id_);

        b2CircleShape tst_shape;
        tst_shape.m_p.Set(0.0f, 0.0f);
        tst_shape.m_radius = 1.0f;
        b2FixtureDef robo_fixtur;
        robo_fixtur.density = 1.f;
        robo_fixtur.friction = 0.7f;
        robo_fixtur.shape = &tst_shape;
        robo_fixtur.restitution = 0.1f;
        //body_->CreateFixture(&robo_fixtur);

        b2PolygonShape body_shape;
        float offset_x = 0.0f, offset_y = -1.f;
        b2Vec2 points[4] = {
            b2Vec2(-size.x/2 + offset_x, -size.y/2 + offset_y),
            b2Vec2(size.x/2 + offset_x, -size.y/2 + offset_y),
            b2Vec2(size.x/2 + offset_x, size.y/2 + offset_y),
            b2Vec2(-size.x/2 + offset_x, size.y/2 + offset_y)
        };
        body_shape.Set(points, 4);
        //body_shape.SetAsBox(size.x/2,size.y/2);
        b2FixtureDef body_shape_fixture;
        body_shape_fixture.density = 1.f;
        body_shape_fixture.shape = &body_shape;
        //body_->CreateFixture(&body_shape_fixture);

        //shape definition for main fixture
        b2PolygonShape polygonShape;
        polygonShape.SetAsBox(0.1, 0.5, b2Vec2(0, 0.6), 0); 

        //fixture definition
        b2FixtureDef foot_fixture;
        foot_fixture.shape = &polygonShape;
        foot_fixture.density = 1;
        foot_fixture.isSensor = true;
        foot_fixture.userData = (void*)&id_;

        auto fixtures = {robo_fixtur, body_shape_fixture, foot_fixture};
        auto physics = add_component<rh::components::Physics>(roboBodyDef, fixtures);
        physics->body->SetFixedRotation(true);
    }

    void Robo::update(const sf::Time &t) {
        //shader.setParameter("blur_radius", 0.03f);
        //shader.setParameter("sigma", 3.5f);
        //shader.setParameter("glowMultiplier", 1.5f);
        //shader.setParameter("width", 500.f);
        circle.setRotation(t.asSeconds()*1000);
    }

}
