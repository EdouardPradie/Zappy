/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Victory
*/

#pragma once

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string_view>
#include <vector>
#include <zappy/MusicManager/MusicManager.hh>
#include <zappy/Scenes/AScene.hh>

constexpr std::string_view VICTORY_MUSIC{"./gui/assets/music/victoryismine.ogg"};
constexpr std::string_view VICTORY_SCREEN{"./gui/assets/sprites/win.png"};

namespace zappy
{

    class Victory : public AScene
    {
        public:
            Victory(MusicManager &music_manager);
            Victory(Victory const &to_copy) = delete;
            Victory(Victory &&to_move) = delete;
            ~Victory() override = default;

            Victory &operator=(Victory const &to_copy) = delete;
            Victory &operator=(Victory &&to_move) = delete;

            void setVictoryTeam(const std::string &name);
            void draw(sf::RenderWindow &window) override;
            void manageEvent(sf::RenderWindow &window, sf::Event &event,
                             std::vector<std::string> &command_to_send) override;

        private:
            sf::Font m_font;
            sf::Text m_text;
            sf::Music m_music;
            sf::View m_view;

            MusicManager &m_music_manager;
    };

} // namespace zappy
