/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** SelectionPanel
*/

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <zappy/HUD/SelectionPanel.hh>
#include <zappy/Player/Player.hh>

// Constructor && Destructor

zappy::SelectionPanel::SelectionPanel(std::vector<Player> &players) : m_players{players}
{
    m_panel.m_rect.left = 320;
    m_panel.m_rect.top = 144;
    m_panel.m_rect.width = 278;
    m_panel.m_rect.height = 494;
    m_panel.m_position = {0, 0};
    m_view.setViewport({0.F, 0.1F, 0.225F, 0.6F});
    m_standard_team = {600, 20};
    m_standard_id = {400, 20};
    m_standard_position = {500, 80};
    m_global_position = {0, 0};
    m_standard_sprite = {100, 0};
    m_standard_rect = {100, 0};
    m_shape.setSize({900, 160});
}

// Methods

void zappy::SelectionPanel::draw(sf::RenderWindow &window, sf::Sprite &sprite, sf::Text &text)
{
    auto compare = [](Player &player1, Player &player2) {
        return player1.getId() < player2.getId();
    };
    sf::Color original_color = sprite.getColor();
    sf::View original_view = window.getView();
    sf::Vector2f local_position{0, 0};

    std::sort(m_players.begin(), m_players.end(), compare);
    animatePanel();
    sprite.setColor({255, 255, 255});
    sprite.scale(0.3F, 0.25F);
    sprite.setOrigin(0, 0);
    sprite.setTextureRect(m_panel.m_rect);
    sprite.setPosition(m_panel.m_position);
    window.draw(sprite);
    window.setView(m_view);
    sprite.setScale(8, 5.5);
    text.setCharacterSize(70);
    updateShapes();
    for (auto &shape : m_tiles) {
        m_shape.setPosition(m_standard_rect + m_global_position + local_position);
        m_shape.setFillColor(shape.m_color);
        shape.m_box = m_shape.getGlobalBounds();
        window.draw(m_shape);
        local_position.y += 150;
    }
    local_position.y = 0;
    for (auto &player : m_players) {
        sprite.setTextureRect({0, 274 + 320 * (player.getLevel() - 1), 32, 32});
        sprite.setPosition(m_standard_sprite + local_position + m_global_position);
        window.draw(sprite);
        text.setPosition(m_standard_id + local_position + m_global_position);
        text.setString("Id : " + std::to_string(player.getId()));
        window.draw(text);
        text.setPosition(m_standard_team + local_position + m_global_position);
        text.setString("Team : " + player.getTeam());
        window.draw(text);
        text.setPosition(m_standard_position + local_position + m_global_position);
        text.setString("Position : (" + std::to_string(player.getLocalPosition().x) + ", " +
                       std::to_string(player.getLocalPosition().y) + ")");
        window.draw(text);
        local_position.y += 150;
    }
    m_last.y = local_position.y;
    sprite.setColor(original_color);
    window.setView(original_view);
}

void zappy::SelectionPanel::updateShapes()
{
    size_t players = m_players.size();
    size_t tiles = m_tiles.size();

    if (players > tiles) {
        while (m_tiles.size() < players)
            m_tiles.emplace_back();
    } else if (players < tiles) {
        while (m_tiles.size() > players)
            m_tiles.pop_back();
    }
}

void zappy::SelectionPanel::manageEvent(sf::RenderWindow &window, sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
        m_is_active = !m_is_active;
    if (event.type == sf::Event::MouseWheelScrolled && m_is_active) {
        if (event.mouseWheelScroll.delta > 0 &&
            m_last.y + m_global_position.y + 50 > m_view.getSize().y)
            m_global_position.y -= 5;
        else if (event.mouseWheelScroll.delta < 0 && m_global_position.y < 0)
            m_global_position.y += 5;
    }
    checkSelection(window, event);
}

void zappy::SelectionPanel::checkSelection(sf::RenderWindow &window, sf::Event &event)
{
    auto compare = [](Player &player1, Player &player2) {
        return player1.getId() < player2.getId();
    };

    std::sort(m_players.begin(), m_players.end(), compare);
    for (size_t iterator = 0; iterator < m_tiles.size(); iterator += 1) {
        if (event.type == sf::Event::MouseMoved && !m_tiles[iterator].m_selected &&
            m_tiles[iterator].m_box.contains(
                window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y}, m_view)))
            m_tiles[iterator].m_color = {190, 158, 121};
        else if (event.type == sf::Event::MouseButtonPressed &&
                 m_tiles[iterator].m_box.contains(
                     window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y}, m_view))) {
            resetSelection();
            m_selection_id = iterator;
            m_tiles[iterator].m_selected = true;
            m_tiles[iterator].m_color = {132, 85, 31};
            m_is_selected = true;
            break;
        } else if (!m_tiles[iterator].m_selected) {
            m_tiles[iterator].m_color = {209, 186, 159};
        }
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        m_is_selected = false;
        resetSelection();
    }
}

void zappy::SelectionPanel::resetSelection()
{
    for (auto &tile : m_tiles) {
        tile.m_color = {209, 186, 159};
        tile.m_selected = false;
    }
}

void zappy::SelectionPanel::animatePanel()
{
    if (m_is_active && m_clock.getElapsedTime().asMicroseconds() > 1.F &&
        m_panel.m_position.x < 0) {
        m_clock.restart();
        m_panel.m_position.x += 10;
        m_standard_position.x += 10 * 4.4F;
        m_standard_id.x += 10 * 4.4F;
        m_standard_sprite.x += 10 * 4.4F;
        m_standard_team.x += 10 * 4.4F;
        m_standard_rect.x += 10 * 4.4F;
    } else if (!m_is_active && m_clock.getElapsedTime().asMicroseconds() > 1.F &&
               m_panel.m_position.x > -278) {
        m_clock.restart();
        m_panel.m_position.x -= 10;
        m_standard_position.x -= 10 * 4.4F;
        m_standard_id.x -= 10 * 4.4F;
        m_standard_sprite.x -= 10 * 4.4F;
        m_standard_team.x -= 10 * 4.4F;
        m_standard_rect.x -= 10 * 4.4F;
    }
}

bool zappy::SelectionPanel::isPlayerSelected() const
{
    return m_is_selected && m_is_active;
}

zappy::Player &zappy::SelectionPanel::getSelectedPlayer() const
{
    auto compare = [](Player &player1, Player &player2) {
        return player1.getId() < player2.getId();
    };
    
    std::sort(m_players.begin(), m_players.end(), compare);
    return m_players[m_selection_id];
}
