/*
** EPITECH PROJECT, 2023
** gui
** File description:
** AParticle
*/

#include <SFML/System/Vector2.hpp>
#include <zappy/ParticleEngine/AParticle.hh>

// Constructor && Destructor

// Methods

void zappy::AParticle::draw(sf::RenderWindow &window)
{
    window.draw(m_shape);
}

void zappy::AParticle::moveShape()
{
    resetPosition();
    m_shape.move(m_velocity);
}

void zappy::AParticle::resetPosition()
{
}

bool zappy::AParticle::canDelete() const
{
    return m_delete;
}

void zappy::AParticle::setDelete()
{
    m_must_be_delete = true;
}
