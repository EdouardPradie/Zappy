/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Map
*/

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <ostream>
#include <vector>
#include <zappy/Map/Map.hh>
#include <zappy/Map/Tile.hh>

// Constructor && Destructor

zappy::Map::Map(int width, int height)
{
    int random = 0;
    zappy::Tile tile = {};

    std::srand(static_cast<unsigned int>(time(nullptr)));
    for (size_t x_value = 0; x_value < static_cast<size_t>(width); x_value += 1) {
        m_map.emplace_back();
        for (size_t y_value = 0; y_value < static_cast<size_t>(height); y_value += 1) {
            random = std::rand() % TILE_NUMBER;
            tile.m_position = {static_cast<float>(x_value) * (TILE_SIZE * SCALING),
                               static_cast<float>(y_value) * (TILE_SIZE * SCALING)};
            tile.m_rect = {random * TILE_SIZE + 61, 56, TILE_SIZE, TILE_SIZE};
            m_map[x_value].emplace_back(tile);
        }
    }
    m_map[0][0].m_inventory.linemate = 100;
    m_map[0][1].m_inventory.linemate = 50;
    m_cursor.m_rect = {61, 72, TILE_SIZE, TILE_SIZE};
    m_cursor_rect[0] = m_cursor.m_rect;
    m_cursor_rect[1] = {61 + TILE_SIZE, 72, TILE_SIZE, TILE_SIZE};
}

// Methods

void zappy::Map::draw(sf::RenderWindow &window, sf::Sprite &sprite)
{
    for (auto &columns : m_map) {
        for (auto &tile : columns) {
            sprite.setTextureRect(tile.m_rect);
            sprite.setPosition(tile.m_position);
            tile.m_box = sprite.getGlobalBounds();
            sprite.setScale(sf::Vector2f{SCALING, SCALING});
            window.draw(sprite);
        }
    }
    if (m_is_cursor_active) {
        animateCursor();
        sprite.setTextureRect(m_cursor_rect[m_cursor_index]);
        sprite.setPosition(m_cursor.m_position);
        window.draw(sprite);
    }
}

bool zappy::Map::selectTile(sf::Event &event, sf::RenderWindow &window)
{
    sf::Vector2i tmp{event.mouseButton.x, event.mouseButton.y};
    const sf::Vector2f point = window.mapPixelToCoords(tmp);
    bool is_touched = false;

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        for (auto height : m_map) {
            for (auto width : height) {
                if (width.m_box.contains(point)) {
                    m_is_cursor_active = true;
                    m_cursor.m_position = width.m_position;
                    m_selected_tile = width;
                    is_touched = true;
                    break;
                }
            }
        }
        if (!is_touched)
            m_is_cursor_active = false;
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        m_is_cursor_active = false;
    return m_is_cursor_active;
}

std::vector<std::vector<zappy::Tile>> zappy::Map::getMap() const
{
    return m_map;
}

void zappy::Map::animateCursor()
{
    if (m_cursor_clock.getElapsedTime().asSeconds() > static_cast<float>(0.5)) {
        m_cursor_index += 1;
        m_cursor_clock.restart();
    }
    if (m_cursor_index > 1)
        m_cursor_index = 0;
}

zappy::Tile &zappy::Map::getSelectedTile()
{
    return m_selected_tile;
};

void zappy::Map::modifyTile(Bct &arg)
{
    m_map[static_cast<size_t>(arg.x_tile_coord)][static_cast<size_t>(arg.y_tile_coord)]
        .m_inventory.food = static_cast<unsigned int>(arg.ressources[0]);
    m_map[static_cast<size_t>(arg.x_tile_coord)][static_cast<size_t>(arg.y_tile_coord)]
        .m_inventory.linemate = static_cast<unsigned int>(arg.ressources[1]);
    m_map[static_cast<size_t>(arg.x_tile_coord)][static_cast<size_t>(arg.y_tile_coord)]
        .m_inventory.deraumede = static_cast<unsigned int>(arg.ressources[2]);
    m_map[static_cast<size_t>(arg.x_tile_coord)][static_cast<size_t>(arg.y_tile_coord)]
        .m_inventory.sibur = static_cast<unsigned int>(arg.ressources[3]);
    m_map[static_cast<size_t>(arg.x_tile_coord)][static_cast<size_t>(arg.y_tile_coord)]
        .m_inventory.mendiane = static_cast<unsigned int>(arg.ressources[4]);
    m_map[static_cast<size_t>(arg.x_tile_coord)][static_cast<size_t>(arg.y_tile_coord)]
        .m_inventory.phiras = static_cast<unsigned int>(arg.ressources[5]);
    m_map[static_cast<size_t>(arg.x_tile_coord)][static_cast<size_t>(arg.y_tile_coord)]
        .m_inventory.thystame = static_cast<unsigned int>(arg.ressources[6]);
}

void zappy::Map::setCursor(bool status)
{
    m_is_cursor_active = status;
}
