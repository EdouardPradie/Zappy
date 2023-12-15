/*
** EPITECH PROJECT, 2023
** gui
** File description:
** WeatherManager
*/

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <zappy/MusicManager/MusicManager.hh>
#include <zappy/ParticleEngine/ParticleEngine.hh>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <array>

namespace zappy
{

    enum class Weather {
        DAY,
        NIGHT,
        RAINY,
        SNOWY,
        SANDY,
        FOGGY,
    };

    class WeatherManager
    {
        public:
            WeatherManager();
            WeatherManager(WeatherManager const &to_copy) = default;
            WeatherManager(WeatherManager &&to_move) = default;
            ~WeatherManager() = default;

            WeatherManager &operator=(WeatherManager const &to_copy) = default;
            WeatherManager &operator=(WeatherManager &&to_move) = default;

            void checkWeather(zappy::MusicManager &music_manager);
            void draw(sf::RenderWindow &window);

        private:
            void setFilter(bool status);
            void animateFilter();
            void changeWeather(zappy::Weather new_weather, zappy::MusicManager &music_manager);
            void randomMusicSelector(zappy::MusicManager &music_manager);
            void changeDayNight();

            bool m_filter_status = false;
            short m_cycles = 0;
            sf::Clock m_clock;
            sf::Clock m_animation_clock;
            zappy::ParticleEngine m_engine;
            zappy::Weather m_state = Weather::DAY;
            sf::View m_view;
            std::array<Weather, 5> m_weathers;
            sf::RectangleShape m_filter;
            std::vector<std::string> m_music_selector;
    };
} // namespace zappy
