/*
** EPITECH PROJECT, 2023
** gui
** File description:
** GUI
*/

#pragma once

#include "zappy/DisconnectPanel/DisconnectPanel.hh"
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <array>
#include <cstddef>
#include <memory>
#include <string_view>
#include <vector>
#include <zappy/Camera.hh>
#include <zappy/GuiClient/GuiClient.hpp>
#include <zappy/HUD/HUD.hh>
#include <zappy/Map/Map.hh>
#include <zappy/Scenes/Game.hh>
#include <zappy/Scenes/IScene.hh>
#include <zappy/Scenes/SceneManager.hh>
#include <zappy/Scenes/Victory.hh>

constexpr std::string_view GUI_TITLE{"Zappy Gui"};
constexpr unsigned int FRAMELIMIT{60};

constexpr unsigned int WIDTH{1920};
constexpr unsigned int HEIGHT{1080};

namespace zappy
{
    class GUI
    {
        public:
            GUI(const std::string &address, unsigned short port);
            GUI(GUI const &to_copy) = delete;
            GUI(GUI &&to_move) = delete;
            ~GUI() = default;

            GUI &operator=(GUI const &to_copy) = delete;
            GUI &operator=(GUI &&to_move) = delete;

            std::array<std::unique_ptr<IScene>, 3> &getScenes();
            void updateWindow();
            void clearWindow();
            void eventManager();
            void changeScene(size_t index);
            void draw();
            int start();

        private:
            sf::RenderWindow m_window{};

            zappy::SceneManager m_scene_manager{};
            zappy::Client m_client;
            zappy::DisconnectPanel m_error_panel{};
    };

} // namespace zappy
