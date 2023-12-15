/*
** EPITECH PROJECT, 2023
** gui
** File description:
** FrequencyPanel
*/

#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <array>
#include <cstddef>
#include <vector>
#include <zappy/HUD/TextButton.hh>
#include <zappy/Map/Tile.hh>

namespace zappy
{

    class FrequencyPanel
    {
        public:
            FrequencyPanel();
            FrequencyPanel(FrequencyPanel const &to_copy) = default;
            FrequencyPanel(FrequencyPanel &&to_move) = default;
            ~FrequencyPanel() noexcept = default;

            FrequencyPanel &operator=(FrequencyPanel const &to_copy) = delete;
            FrequencyPanel &operator=(FrequencyPanel &&to_move) = delete;

            void draw(sf::RenderWindow &window, sf::Text &text);
            void manageEvent(sf::RenderWindow &window, sf::View &view, sf::Event &event,
                             std::vector<std::string> &command_to_send);

        private:
            void setPosition(sf::RenderWindow &window);
            void setBox(sf::Text &text);

            sf::RectangleShape m_shape{};
            sf::Color m_color{31, 31, 31};

            std::vector<zappy::TextButton> m_buttons{};
            std::array<Text, 4> m_texts{};
            size_t m_frequency_index = 1;
            size_t m_old_index = 1;
    };
} // namespace zappy
