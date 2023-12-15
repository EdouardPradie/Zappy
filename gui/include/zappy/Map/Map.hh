/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Map
*/

#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <array>
#include <cstddef>
#include <string_view>
#include <vector>
#include <zappy/GuiCommand/GuiCommand.hh>
#include <zappy/Map/Tile.hh>

constexpr unsigned int TEXTURE_WIDTH{80};
constexpr unsigned int TEXTURE_HEIGHT{16};
constexpr unsigned int TILESIDE{32};

namespace zappy
{
    class Map
    {
        public:
            Map() = default;
            Map(int width, int height);
            Map(Map const &to_copy) = default;
            Map(Map &&to_move) = default;
            ~Map() = default;

            Map &operator=(Map const &to_copy) = default;
            Map &operator=(Map &&to_move) = default;

            void draw(sf::RenderWindow &window, sf::Sprite &sprite);
            [[nodiscard]] std::vector<std::vector<Tile>> getMap() const;
            [[nodiscard]] bool selectTile(sf::Event &event, sf::RenderWindow &window);
            void modifyTile(Bct &arg);
            void animateCursor();
            void setCursor(bool status);
            Tile &getSelectedTile();

        private:
            std::vector<std::vector<Tile>> m_map{};
            Tile m_cursor{};
            Tile m_selected_tile{};
            std::array<sf::IntRect, 2> m_cursor_rect{};
            sf::Clock m_cursor_clock{};
            std::size_t m_cursor_index = 0;
            bool m_is_cursor_active = false;
    };
} // namespace zappy
