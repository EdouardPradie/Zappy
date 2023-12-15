/*
** EPITECH PROJECT, 2023
** gui
** File description:
** TextButton
*/

#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <string>
#include <zappy/Map/Tile.hh>

namespace zappy
{

    class TextButton
    {
        public:
            TextButton(const std::string &text, bool increment);
            TextButton(TextButton const &to_copy) = default;
            TextButton(TextButton &&to_move) = default;
            ~TextButton() noexcept = default;

            TextButton &operator=(TextButton const &to_copy) = default;
            TextButton &operator=(TextButton &&to_move) = default;

            void draw(sf::RenderWindow &window, sf::Text &text);
            void manageEvent(sf::RenderWindow &window, sf::View &view, sf::Event &event,
                             size_t &index);
            void setPosition(sf::Vector2f &vector);

        private:
            sf::Color m_color{};
            sf::Clock m_clock{};

            Text m_text{};
            bool m_increment{};
    };

} // namespace zappy
