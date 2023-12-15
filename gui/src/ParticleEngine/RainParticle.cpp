/*
** EPITECH PROJECT, 2023
** gui
** File description:
** RainParticle
*/

#include "zappy/ParticleEngine/AParticle.hh"
#include <SFML/System/Vector2.hpp>
#include <iterator>
#include <zappy/ParticleEngine/RainParticle.hh>

// Constructor && Destructor

zappy::RainParticle::RainParticle()
{
    m_shape.setSize(sf::Vector2f{2, 30});
    m_shape.setFillColor(sf::Color{196, 211, 223});
    m_velocity = sf::Vector2f{0.F, static_cast<float>(std::rand() % 20 + 10)};
    m_shape.setPosition(sf::Vector2f{static_cast<float>(std::rand() % 1920),
                                     static_cast<float>(-(std::rand() % 1080))});
    m_delete = false;
}

// Methods

void zappy::RainParticle::draw(sf::RenderWindow &window)
{
    window.draw(m_shape);
    resetPosition();
}

void zappy::RainParticle::resetPosition()
{
    sf::Vector2f position = m_shape.getPosition();

    if (m_must_be_delete && position.y >= 1100) {
        m_delete = true;
        return;
    }
    if (position.y >= 1100) {
        position.y = -100.F;
        m_shape.setPosition(position);
    }
}
