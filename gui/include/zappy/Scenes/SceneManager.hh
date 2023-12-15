/*
** EPITECH PROJECT, 2023
** gui
** File description:
** SceneManager
*/

#pragma once

#include "zappy/MusicManager/MusicManager.hh"
#include "zappy/Scenes/IScene.hh"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <array>
#include <memory>
#include <vector>
#include <zappy/Scenes/AScene.hh>

namespace zappy
{

    enum class Scene {
        MENU = 0,
        GAME = 1,
        WIN = 2,
    };

    class SceneManager : IScene
    {
        public:
            SceneManager();
            SceneManager(SceneManager const &to_copy) = delete;
            SceneManager(SceneManager &&to_move) = delete;
            ~SceneManager() noexcept override = default;

            SceneManager &operator=(SceneManager const &to_copy) = delete;
            SceneManager &operator=(SceneManager &&to_move) = delete;

            void draw(sf::RenderWindow &window) override;
            void manageEvent(sf::RenderWindow &window, sf::Event &event,
                             std::vector<std::string> &command_to_send) override;
            void changeScene(size_t index);
            size_t getSceneIndex() const;
            std::array<std::unique_ptr<IScene>, 3> &getScenes();

        private:
            zappy::MusicManager m_music_manager{};

            std::array<std::unique_ptr<IScene>, 3> m_scenes;
            zappy::Scene m_scene_index{1};
    };

} // namespace zappy
