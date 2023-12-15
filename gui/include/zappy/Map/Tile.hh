/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Tile
*/

#pragma once

#include <Inventory.hh>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

constexpr int TILE_SIZE {16};
constexpr int TILE_NUMBER {5};
constexpr int SCALING {5};

namespace zappy {

    struct Tile {
        sf::Vector2f m_position;
        sf::IntRect m_rect;
        sf::FloatRect m_box;
        Inventory m_inventory;
    };

    struct Text {
        std::string m_str;
        sf::Vector2f m_position;
        sf::IntRect m_rect;
        sf::FloatRect m_box;
    };
}
