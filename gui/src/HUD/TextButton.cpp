/*
** EPITECH PROJECT, 2023
** gui
** File description:
** TextButton
*/

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstddef>
#include <zappy/HUD/TextButton.hh>

// Constructor && Destructor

zappy::TextButton::TextButton(const std::string &text, bool increment) : m_increment{increment}
{
    m_text.m_str = text;
    m_color = {31, 31, 31};
}

// Methods

void zappy::TextButton::draw(sf::RenderWindow &window, sf::Text &text)
{
    text.setString(m_text.m_str);
    text.setFillColor(m_color);
    text.setPosition(m_text.m_position);
    m_text.m_box = text.getGlobalBounds();
    window.draw(text);
}

void zappy::TextButton::manageEvent(sf::RenderWindow &window, sf::View &view, sf::Event &event,
                                    size_t &index)
{
    sf::Vector2i position{event.mouseMove.x, event.mouseMove.y};
    sf::Vector2i click{event.mouseButton.x, event.mouseButton.y};
    sf::Vector2f move_world_position = window.mapPixelToCoords(position, view);
    sf::Vector2f click_world_position = window.mapPixelToCoords(click, view);

    if (event.type == sf::Event::MouseMoved && m_text.m_box.contains(move_world_position)) {
        m_color = {47, 79, 79};
    } else if (event.type == sf::Event::MouseButtonPressed &&
               event.mouseButton.button == sf::Mouse::Left &&
               m_text.m_box.contains(click_world_position) &&
               m_clock.getElapsedTime().asSeconds() > 0.5F) {
        m_clock.restart();
        m_color = {105, 105, 105};
        if (m_increment)
            index += 1;
        else
            index -= 1;
    } else
        m_color = {31, 31, 31};
}

void zappy::TextButton::setPosition(sf::Vector2f &vector)
{
    m_text.m_position = vector;
}
