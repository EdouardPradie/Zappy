/*
** EPITECH PROJECT, 2023
** gui
** File description:
** ParticleEngine
*/

#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <zappy/ParticleEngine/AParticle.hh>
#include <zappy/ParticleEngine/FogParticle.hh>
#include <zappy/ParticleEngine/ParticleEngine.hh>
#include <zappy/ParticleEngine/RainParticle.hh>

// Constructor && Destructor

// Methods

void zappy::ParticleEngine::drawParticles(sf::RenderWindow &window)
{
    moveParticles();
    for (auto &particle : m_particles)
        particle->draw(window);
    deleteParticles();
}

void zappy::ParticleEngine::moveParticles()
{
    if (m_clock.getElapsedTime().asSeconds() < 0.01F)
        return;
    for (auto &particle : m_particles)
        particle->moveShape();
    m_clock.restart();
}

void zappy::ParticleEngine::clear()
{
    m_particles.clear();
}

void zappy::ParticleEngine::createRain()
{
    for (size_t iterator = 0; iterator < 1000; iterator += 1)
        m_particles.push_back(std::make_unique<RainParticle>());
}

void zappy::ParticleEngine::createFog()
{
    for (size_t iterator = 0; iterator < 200; iterator += 1)
        m_particles.push_back(std::make_unique<FogParticle>());
}

void zappy::ParticleEngine::setDelete()
{
    for (auto &particle : m_particles) {
        particle->setDelete();
    }
};

void zappy::ParticleEngine::deleteParticles()
{
    auto iterator = m_particles.begin();

    for (; iterator != m_particles.end();) {
        if (iterator->get()->canDelete())
            iterator = m_particles.erase(iterator);
        else
            ++iterator;
    }
}
