/*
** EPITECH PROJECT, 2023
** gui
** File description:
** FogParticle
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <zappy/ParticleEngine/AParticle.hh>

namespace zappy
{

    class FogParticle : public AParticle
    {
        public:
            FogParticle();
            FogParticle(FogParticle const &to_copy) = default;
            FogParticle(FogParticle &&to_move) = default;
            ~FogParticle() override = default;

            FogParticle &operator=(FogParticle const &to_copy) = default;
            FogParticle &operator=(FogParticle &&to_move) = default;

            void draw(sf::RenderWindow &window) final;
            void setDelete() override;

        private:
            void resetPosition() override;
            void animateFog();

            int m_max_alpha;
            sf::Clock m_clock;
    };

} // namespace zappy
