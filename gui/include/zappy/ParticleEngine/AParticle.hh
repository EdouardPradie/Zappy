/*
** EPITECH PROJECT, 2023
** gui
** File description:
** AParticle
*/

#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

namespace zappy
{

    class AParticle
    {
        public:
            AParticle() = default;
            AParticle(AParticle const &to_copy) = default;
            AParticle(AParticle &&to_move) = default;
            virtual ~AParticle() = default;

            AParticle &operator=(AParticle const &to_copy) = default;
            AParticle &operator=(AParticle &&to_move) = default;

            virtual void draw(sf::RenderWindow &window);
            void moveShape();
            virtual void setDelete();
            [[nodiscard]] bool canDelete() const;

        protected:
            virtual void resetPosition();

            sf::RectangleShape m_shape{};
            sf::Vector2f m_velocity{};
            bool m_delete = false;
            bool m_must_be_delete = false;
    };

} // namespace zappy
