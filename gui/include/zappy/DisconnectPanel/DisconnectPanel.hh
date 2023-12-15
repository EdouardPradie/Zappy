/*
** EPITECH PROJECT, 2023
** gui
** File description:
** DisconnectPanel
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <string_view>

constexpr std::string_view PANEL_ERROR_PATH{"./gui/assets/sprites/Error.png"};

namespace zappy
{

    class DisconnectPanel
    {
        public:
            DisconnectPanel();
            DisconnectPanel(DisconnectPanel const &to_copy) = default;
            DisconnectPanel(DisconnectPanel &&to_move) = default;
            ~DisconnectPanel() noexcept = default;

            DisconnectPanel &operator=(DisconnectPanel const &to_copy) = default;
            DisconnectPanel &operator=(DisconnectPanel &&to_move) = default;

            void manageEvent(sf::RenderWindow &window, sf::Event &event) const;
            void draw(sf::RenderWindow &window);
            void triggerPanel();

        private:
            void animatePanel(sf::RenderWindow &window);

            sf::Texture m_texture{};
            sf::Sprite m_sprite{};
            sf::Vector2f m_position{};
            sf::Clock m_clock{};
            sf::View m_view{};

            bool m_is_active = false;
    };
} // namespace zappy
