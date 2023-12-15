/*
** EPITECH PROJECT, 2023
** gui
** File description:
** SceneManager
*/

#include <cstddef>
#include <zappy/Scenes/Game.hh>
#include <zappy/Scenes/SceneManager.hh>
#include <zappy/Scenes/Victory.hh>

// Constructor && Destructor

zappy::SceneManager::SceneManager()
{
    m_scenes[1] = std::make_unique<Game>(m_music_manager);
    m_scenes[2] = std::make_unique<Victory>(m_music_manager);
}

// Methods

void zappy::SceneManager::draw(sf::RenderWindow &window)
{
    m_scenes[static_cast<size_t>(m_scene_index)]->draw(window);
}

void zappy::SceneManager::manageEvent(sf::RenderWindow &window, sf::Event &event,
                                      std::vector<std::string> &command_to_send)
{
    m_scenes[static_cast<size_t>(m_scene_index)]->manageEvent(window, event, command_to_send);
}

std::array<std::unique_ptr<zappy::IScene>, 3> &zappy::SceneManager::getScenes()
{
    return m_scenes;
}

void zappy::SceneManager::changeScene(size_t index)
{
    m_scene_index = static_cast<Scene>(index);
}

size_t zappy::SceneManager::getSceneIndex() const
{
    return static_cast<size_t>(m_scene_index);
}
