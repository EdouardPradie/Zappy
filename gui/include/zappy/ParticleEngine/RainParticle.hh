/*
** EPITECH PROJECT, 2023
** gui
** File description:
** RainParticle
*/

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <zappy/ParticleEngine/AParticle.hh>

namespace zappy
{

    class RainParticle : public AParticle
    {
        public:
            RainParticle();
            RainParticle(RainParticle const &to_copy) = default;
            RainParticle(RainParticle &&to_move) = default;
            ~RainParticle() override = default;

            RainParticle &operator=(RainParticle const &to_copy) = default;
            RainParticle &operator=(RainParticle &&to_move) = default;

            void draw(sf::RenderWindow &window) final;

        private:
            void resetPosition() final;
    };
} // namespace zappy
