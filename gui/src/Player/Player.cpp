/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Player
*/

#include <Inventory.hh>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <ios>
#include <ostream>
#include <utility>
#include <zappy/Map/Tile.hh>
#include <zappy/Player/Player.hh>

// Constructor && Destructor

zappy::Player::Player(const zappy::PlayerInfo &infos)
    : m_id{infos.m_id}, m_level{infos.m_level}, m_orientation{infos.m_orientation},
      m_position{static_cast<int>(infos.m_x), static_cast<int>(infos.m_y)}, m_team{infos.m_team}
{
    m_position_map.x = m_position.x * TILE_SIZE * SCALING + (TILE_SIZE * SCALING / 2);
    m_position_map.y = m_position.y * TILE_SIZE * SCALING + (TILE_SIZE * SCALING / 2);
    m_is_dead = false;
    m_delete = false;
}

// Methods

int zappy::Player::getId() const
{
    return m_id;
}

void zappy::Player::setPlayerLevel(int level)
{
    m_level = level;
}

void zappy::Player::drawPlayer(sf::RenderWindow &window, sf::Sprite &sprite, sf::Vector2i &size)
{
    animatePlayer(size);
    sprite.setOrigin({16, 26});
    sprite.setPosition(m_position_map);
    sprite.setTextureRect(m_rect);
    sprite.setColor(m_color);
    m_box = sprite.getGlobalBounds();
    m_box.left += 11 * SCALING;
    m_box.width -= 22 * SCALING;
    m_box.top += 5 * SCALING;
    m_box.height -= 8 * SCALING;
    window.draw(sprite);
    sprite.setOrigin({0, 0});
    sprite.setColor(sf::Color{255, 255, 255});
}

void zappy::Player::movePlayer(int pos_x, int pos_y, Orientation orientation)
{
    m_orientation = orientation;
    m_position.x = pos_x;
    m_position.y = pos_y;

    m_position_map.x = m_position.x * TILE_SIZE * SCALING + (TILE_SIZE * SCALING / 2);
    m_position_map.y = m_position.y * TILE_SIZE * SCALING + (TILE_SIZE * SCALING / 2);
}

void zappy::Player::animatePlayer(sf::Vector2i &size)
{
    if (m_is_dead) {
        animateDeath();
        return;
    }
    playerMovement();
    if (m_selected)
        animateSelected();
    if (m_elevate) {
        animateElevation();
        return;
    }
    if (m_orientation == Orientation::North)
        animateNorth(size);
    if (m_orientation == Orientation::East)
        animateEast(size);
    if (m_orientation == Orientation::South)
        animateSouth(size);
    if (m_orientation == Orientation::West)
        animateWest(size);
}

void zappy::Player::animateNorth(sf::Vector2i &size)
{
    checkBoundaries(size);
    if (m_remain.y == 0.F) {
        m_rect = {96, 274 + (320 * (m_level - 1)), 32, 32};
        return;
    }
    if (m_expulse) {
        expulsedSouth();
        return;
    }
    if (m_rect.top != 242 + (320 * (m_level - 1)))
        m_rect = {0, 242 + (320 * (m_level - 1)), 32, 32};
    if (m_clock.getElapsedTime().asSeconds() > 0.07F) {
        m_rect.left += m_rect.width;
        if (m_rect.left / 32 >= 10)
            m_rect.left = 0;
        m_clock.restart();
    }
}

void zappy::Player::animateEast(sf::Vector2i &size)
{
    checkBoundaries(size);
    if (m_remain.x == 0.F) {
        m_rect = {64, 274 + (320 * (m_level - 1)), 32, 32};
        return;
    }
    if (m_expulse) {
        expulsedEast();
        return;
    }
    if (m_rect.top != 146 + (320 * (m_level - 1)))
        m_rect = {0, 146 + (320 * (m_level - 1)), 32, 32};
    if (m_clock.getElapsedTime().asSeconds() > 0.07F) {
        m_rect.left += m_rect.width;
        if (m_rect.left / 32 >= 10)
            m_rect.left = 0;
        m_clock.restart();
    }
}

void zappy::Player::animateSouth(sf::Vector2i &size)
{
    checkBoundaries(size);
    if (m_remain.y == 0.F) {
        m_rect = {0, 274 + (320 * (m_level - 1)), 32, 32};
        return;
    }
    if (m_expulse) {
        expulsedNorth();
        return;
    }
    if (m_rect.top != 178 + (320 * (m_level - 1)))
        m_rect = {0, 178 + (320 * (m_level - 1)), 32, 32};
    if (m_clock.getElapsedTime().asSeconds() > 0.07F) {
        m_rect.left += m_rect.width;
        if (m_rect.left / 32 >= 10)
            m_rect.left = 0;
        m_clock.restart();
    }
}

void zappy::Player::animateWest(sf::Vector2i &size)
{
    checkBoundaries(size);
    if (m_remain.x == 0.F) {
        m_rect = {32, 274 + (320 * (m_level - 1)), 32, 32};
        return;
    }
    if (m_expulse) {
        expulsedWest();
        return;
    }
    if (m_rect.top != 210 + (320 * (m_level - 1)))
        m_rect = {0, 210 + (320 * (m_level - 1)), 32, 32};
    if (m_clock.getElapsedTime().asSeconds() > 0.07F) {
        m_rect.left += m_rect.width;
        if (m_rect.left / 32 >= 10)
            m_rect.left = 0;
        m_clock.restart();
    }
}

sf::Vector2f zappy::Player::getWorldPosition() const
{
    return m_position_map;
}

sf::Vector2i zappy::Player::getLocalPosition() const
{
    return m_position;
}

void zappy::Player::setPlayerInventory(Inventory &inventory)
{
    m_inventory = inventory;
}

zappy::Inventory zappy::Player::getInventory() const
{
    return m_inventory;
}

void zappy::Player::animateDeath()
{
    if (m_rect.top != 306 + (320 * (m_level - 1))) {
        m_rect.top = 306 + (320 * (m_level - 1));
        m_rect.left = 0;
    }
    if (m_clock.getElapsedTime().asSeconds() > 0.1F && m_rect.left < 128) {
        m_rect.left += m_rect.width;
        m_clock.restart();
    }
    if (m_rect.left >= 128 && m_clock.getElapsedTime().asSeconds() > 0.02F) {
        m_color.a -= 1;
        if (m_color.a <= 0)
            m_delete = true;
        m_clock.restart();
    }
}

void zappy::Player::triggerDeath()
{
    m_is_dead = true;
}

bool zappy::Player::canDeletePlayer() const
{
    return m_delete;
}

sf::FloatRect zappy::Player::getColliderBox() const
{
    return m_box;
}

void zappy::Player::animateSelected()
{
    if (m_clock_selected.getElapsedTime().asMilliseconds() > 1.F && m_spark) {
        m_clock_selected.restart();
        m_color.a -= 1;
        if (m_color.a == 123)
            m_spark = !m_spark;
    }
    if (m_clock_selected.getElapsedTime().asMilliseconds() > 1.F && !m_spark) {
        m_clock_selected.restart();
        m_color.a += 1;
        if (m_color.a == 255)
            m_spark = !m_spark;
    }
}

void zappy::Player::triggerSelection(bool status)
{
    m_selected = status;
    if (!m_selected) {
        if (!m_is_dead)
            m_color.a = 255;
        m_spark = true;
    }
}

const std::string &zappy::Player::getTeam() const
{
    return m_team;
}

int zappy::Player::getLevel() const
{
    return m_level;
}

void zappy::Player::triggerExpulse()
{
    m_expulse = true;
}

void zappy::Player::expulsedEast()
{
    if (m_rect.top != 370 + (320 * (m_level - 1)))
        m_rect = {0, 370 + (320 * (m_level - 1)), 32, 32};
    if (m_clock.getElapsedTime().asSeconds() > 0.07F) {
        if (m_rect.left < 320)
            m_rect.left += m_rect.width;
        if (m_rect.left >= 320)
            m_expulse = false;
        m_clock.restart();
    }
}

void zappy::Player::expulsedNorth()
{
    if (m_rect.top != 338 + (320 * (m_level - 1)))
        m_rect = {0, 338 + (320 * (m_level - 1)), 32, 32};
    if (m_clock.getElapsedTime().asSeconds() > 0.07F) {
        if (m_rect.left < 320)
            m_rect.left += m_rect.width;
        if (m_rect.left >= 320)
            m_expulse = false;
        m_clock.restart();
    }
}

void zappy::Player::expulsedSouth()
{
    if (m_rect.top != 402 + (320 * (m_level - 1)))
        m_rect = {0, 402 + (320 * (m_level - 1)), 32, 32};
    if (m_clock.getElapsedTime().asSeconds() > 0.07F) {
        if (m_rect.left < 320)
            m_rect.left += m_rect.width;
        if (m_rect.left >= 320)
            m_expulse = false;
        m_clock.restart();
    }
}

void zappy::Player::expulsedWest()
{
    if (m_rect.top != 434 + (320 * (m_level - 1)))
        m_rect = {0, 434 + (320 * (m_level - 1)), 32, 32};
    if (m_clock.getElapsedTime().asSeconds() > 0.07F) {
        if (m_rect.left < 320)
            m_rect.left += m_rect.width;
        if (m_rect.left >= 320)
            m_expulse = false;
        m_clock.restart();
    }
}

void zappy::Player::playerMovement()
{
    if (m_remain.x < 0) {
        m_position_map.x += 10;
        m_remain.x += 10;
        return;
    }
    if (m_remain.x > 0) {
        m_position_map.x -= 10;
        m_remain.x -= 10;
        return;
    }
    if (m_remain.y < 0) {
        m_position_map.y += 10;
        m_remain.y += 10;
        return;
    }
    if (m_remain.y > 0) {
        m_position_map.y -= 10;
        m_remain.y -= 10;
        return;
    }
}

void zappy::Player::checkBoundaries(sf::Vector2i &size)
{
    if (m_position_map.x < 0)
        m_position_map.x = size.x * TILE_SIZE * SCALING;
    if (m_position_map.y > size.y * TILE_SIZE * SCALING)
        m_position_map.y = 0;
    if (m_position_map.x > size.x * TILE_SIZE * SCALING)
        m_position_map.x = 0;
    if (m_position_map.y < 0)
        m_position_map.y = size.y * TILE_SIZE * SCALING;
}

void zappy::Player::animateElevation()
{
    if (m_clock.getElapsedTime().asSeconds() >= 1.F) {
        m_clock.restart();
        if (m_rect.left != 288) {
            m_rect.left = 288;
            m_rect.top = 274 + (320 * (m_level - 1));
        }
        if (m_rect.top == 274 + (320 * (m_level - 1)))
            m_rect.top = 274 + (320 * m_level);
        else if (m_rect.top == 274 + (320 * m_level))
            m_rect.top = 274 + (320 * (m_level - 1));
    }
}

void zappy::Player::triggerElevation(bool status)
{
    m_elevate = status;
}

bool zappy::Player::getDeathStatus() const
{
    return m_is_dead;
}
