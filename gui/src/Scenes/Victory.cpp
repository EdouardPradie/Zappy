/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Victory
*/

#include "zappy/MusicManager/MusicManager.hh"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <zappy/HUD/HUD.hh>
#include <zappy/Scenes/Victory.hh>

// Constructor && Destructor

zappy::Victory::Victory(zappy::MusicManager &music_manager) : m_music_manager{music_manager}
{
    m_music.setVolume(25.F);
    m_music.openFromFile(VICTORY_MUSIC.data());
    m_texture.loadFromFile(VICTORY_SCREEN.data());
    m_sprite.setTexture(m_texture);
    m_font.loadFromFile(MAIN_FONT.data());
    m_text.setCharacterSize(100);
    m_text.setFont(m_font);
    m_text.setFillColor({66, 67, 66});
}

// Methods

void zappy::Victory::setVictoryTeam(const std::string &name)
{
    sf::Vector2f position{};
    sf::FloatRect rect{};
    sf::Vector2u size = m_texture.getSize();
    sf::Vector2f factor{m_view.getSize().x / size.x, m_view.getSize().y / size.y};

    m_text.setString(name + " wins !");
    rect = m_text.getGlobalBounds();
    position.x = m_view.getSize().x / 2 - rect.width / 2;
    position.y = m_view.getSize().y / 2 - rect.height / 2;
    m_sprite.setScale(factor);
    m_text.setPosition(position);
    m_music_manager.loadNewMusic(VICTORY_MUSIC.data());
}

void zappy::Victory::manageEvent(sf::RenderWindow &window, sf::Event &event,
                                 [[maybe_unused]] std::vector<std::string> &command_to_send)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        window.close();
}

void zappy::Victory::draw(sf::RenderWindow &window)
{
    sf::View default_view = window.getDefaultView();

    window.setView(m_view);
    m_music_manager.fade();
    window.draw(m_sprite);
    window.draw(m_text);
    window.setView(default_view);
}
