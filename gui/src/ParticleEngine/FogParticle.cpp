/*
** EPITECH PROJECT, 2023
** gui
** File description:
** FogParticle
*/

#include <SFML/System/Vector2.hpp>
#include <zappy/ParticleEngine/FogParticle.hh>

// Constructor && Destructor

zappy::FogParticle::FogParticle()
{
    m_velocity = {static_cast<float>((std::rand() % 5 + 1) / 1.5F), 0};
    m_max_alpha = std::rand() % 20 + 80;
    m_shape.setSize(
        {static_cast<float>(std::rand() % 200 + 100), static_cast<float>(std::rand() % 50 + 100)});
    m_shape.setPosition(
        {static_cast<float>(std::rand() % 2200 - 2000), static_cast<float>(std::rand() % 1080)});
    m_shape.setFillColor({167, 165, 172, 0});
}

// Methods

void zappy::FogParticle::draw(sf::RenderWindow &window)
{
    animateFog();
    window.draw(m_shape);
    resetPosition();
}

void zappy::FogParticle::resetPosition()
{
    sf::Vector2f position = m_shape.getPosition();

    if (position.x > 2000)
        m_shape.setPosition({-500, position.y});
}

void zappy::FogParticle::animateFog()
{
    sf::Color color = m_shape.getFillColor();

    if (!m_must_be_delete && color.a < m_max_alpha &&
        m_clock.getElapsedTime().asSeconds() > 0.05F) {
        m_clock.restart();
        color.a += 1;
        m_shape.setFillColor(color);
    }
    if (m_must_be_delete && color.a > 0 && m_clock.getElapsedTime().asSeconds() > 0.05F) {
        m_clock.restart();
        color.a -= 1;
        m_shape.setFillColor(color);
        if (color.a == 0)
            m_delete = true;
    }
}

void zappy::FogParticle::setDelete()
{
    m_must_be_delete = true;
}
