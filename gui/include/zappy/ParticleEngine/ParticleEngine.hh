/*
** EPITECH PROJECT, 2023
** gui
** File description:
** ParticleEngine
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>
#include <zappy/ParticleEngine/AParticle.hh>

namespace zappy
{

    class ParticleEngine
    {
        public:
            ParticleEngine() = default;
            ParticleEngine(ParticleEngine const &to_copy) = default;
            ParticleEngine(ParticleEngine &&to_move) = default;
            ~ParticleEngine() = default;

            ParticleEngine &operator=(ParticleEngine const &to_copy) = default;
            ParticleEngine &operator=(ParticleEngine &&to_move) = default;

            void createRain();
            void createFog();
            void drawParticles(sf::RenderWindow &window);
            void setDelete();
            void deleteParticles();
            void clear();

        private:
            void moveParticles();
            void fillParticles();

            std::vector<std::unique_ptr<AParticle>> m_particles;
            sf::Clock m_clock;
    };

} // namespace zappy
