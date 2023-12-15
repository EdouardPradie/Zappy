/*
** EPITECH PROJECT, 2023
** gui
** File description:
** DisconnectPanel
*/

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <zappy/DisconnectPanel/DisconnectPanel.hh>

// Constructor && Destructor

zappy::DisconnectPanel::DisconnectPanel()
{
    float pos_x;
    float pos_y;

    m_texture.loadFromFile(PANEL_ERROR_PATH.data());
    pos_x = m_view.getCenter().x - (m_texture.getSize().x / 2 * 0.7F);
    pos_y = m_texture.getSize().y * 1.4F;
    pos_y *= -1;
    m_sprite.setPosition(pos_x, pos_y);
    m_position = m_sprite.getPosition();
}

// Methods

void zappy::DisconnectPanel::manageEvent(sf::RenderWindow &window, sf::Event &event) const
{
    if (event.type == sf::Event::KeyPressed && m_is_active)
        window.close();
}

void zappy::DisconnectPanel::draw(sf::RenderWindow &window)
{
    sf::View original_view = window.getView();

    m_sprite.setTexture(m_texture);
    m_sprite.setScale(0.7F, 1.4F);
    window.setView(m_view);
    animatePanel(window);
    window.draw(m_sprite);
    window.setView(original_view);
}

void zappy::DisconnectPanel::triggerPanel()
{
    m_is_active = true;
}

void zappy::DisconnectPanel::animatePanel(sf::RenderWindow &window)
{
    sf::View view = window.getView();

    if (m_is_active && m_position.y < (view.getSize().y / 2) - (m_texture.getSize().y * 1.4F / 2) &&
        m_clock.getElapsedTime().asMicroseconds() > 1.F) {
        m_clock.restart();
        m_position.y += 20;
        m_sprite.setPosition(m_position);
    }
}
