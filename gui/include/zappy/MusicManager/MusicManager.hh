/*
** EPITECH PROJECT, 2023
** gui
** File description:
** MusicManager
*/

#pragma once

#include <SFML/Audio/Music.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <string_view>

constexpr std::string_view MUSIC_DAY_1{"./gui/assets/music/darkworld.ogg"};
constexpr std::string_view MUSIC_DAY_2{"./gui/assets/music/hyrulefield.ogg"};
constexpr std::string_view MUSIC_RAINY_1{"./gui/assets/music/songofstorms.ogg"};
constexpr std::string_view MUSIC_NIGHT_1{"./gui/assets/music/insidehouse.ogg"};
constexpr std::string_view MUSIC_NIGHT_2{"./gui/assets/music/stonetower.ogg"};
constexpr std::string_view MUSIC_FOGGY_1{"./gui/assets/music/lostwoods.ogg"};
constexpr std::string_view MUSIC_FOGGY_2{"./gui/assets/music/dragonroost.ogg"};

namespace zappy
{

    class MusicManager
    {
        public:
            MusicManager();
            MusicManager(MusicManager const &to_copy) = delete;
            MusicManager(MusicManager &&to_move) = delete;
            ~MusicManager() = default;

            MusicManager &operator=(MusicManager const &to_copy) = delete;
            MusicManager &operator=(MusicManager &&to_move) = delete;

            void fade();
            void loadNewMusic(const std::string &str);
            void playMusic();
            void pauseMusic();

        private:
            sf::Music m_music{};
            sf::Clock m_clock{};

            bool m_fade_in = false;
            bool m_fade_out = false;
            std::string m_music_path{};
    };

} // namespace zappy
