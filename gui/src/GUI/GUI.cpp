/*
** EPITECH PROJECT, 2023
** gui
** File description:
** GUI
*/

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>
#include <tuple>
#include <vector>
#include <zappy/GUI/GUI.hh>
#include <zappy/Map/Map.hh>
#include <zappy/Map/Tile.hh>
#include <zappy/Scenes/Game.hh>
#include <zappy/Scenes/IScene.hh>
#include <zappy/Scenes/SceneManager.hh>
#include <zappy/Scenes/Victory.hh>

// Constructor && Destructor

zappy::GUI::GUI(const std::string &address, unsigned short port)
    : m_window{{WIDTH, HEIGHT}, GUI_TITLE.data()}, m_client{address, port}
{
    m_window.setFramerateLimit(FRAMELIMIT);
}

// Methods

int zappy::GUI::start()
{
    m_client.WelcomeSuppressor();
    m_client.sendGraphic();
    while (m_window.isOpen()) {
        m_window.clear(sf::Color{74, 173, 74});
        eventManager();
        m_scene_manager.draw(m_window);
        m_error_panel.draw(m_window);
        m_window.display();
        m_client.receiveCommand(m_scene_manager, m_window);
        m_client.sendCommand("mct\n");
        if (m_client.getSocketStatus() == sf::Socket::Disconnected &&
            m_scene_manager.getSceneIndex() == 1)
            m_error_panel.triggerPanel();
    }
    return 0;
}

void zappy::GUI::eventManager()
{
    sf::Event event{};
    std::vector<std::string> command_to_send{};

    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();
        m_scene_manager.manageEvent(m_window, event, command_to_send);
        m_error_panel.manageEvent(m_window, event);
    }
    if (!command_to_send.empty())
        for (std::string str : command_to_send)
            m_client.sendCommand(str);
}
