/*
** EPITECH PROJECT, 2023
** gui
** File description:
** PlayerManager
*/

#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <deque>
#include <memory>
#include <string_view>
#include <vector>
#include <zappy/GuiCommand/GuiCommand.hh>
#include <zappy/Player/Player.hh>

constexpr std::string_view DEATH_SOUND{"./gui/assets/sound/death.ogg"};
constexpr std::string_view INCANTATION_SOUND{"./gui/assets/sound/treasure.ogg"};
constexpr std::string_view INCANTATION_FAILED{"./gui/assets/sound/itemget.ogg"};
constexpr std::string_view INCANTATION_SUCCESS{"./gui/assets/sound/error.ogg"};

namespace zappy
{
    class PlayerManager
    {
        public:
            PlayerManager();
            PlayerManager(PlayerManager const &to_copy) = default;
            PlayerManager(PlayerManager &&to_move) = default;
            ~PlayerManager() = default;

            PlayerManager &operator=(PlayerManager const &to_copy) = default;
            PlayerManager &operator=(PlayerManager &&to_move) = default;
            void changePlayerStats(Pin &inventory);

            void animatePlayers();
            void addPlayer(Pnw &new_player);
            void changePlayerStats(Ppo &position);
            void changePlayerStats(Plv &level);
            void drawPlayers(sf::RenderWindow &window, sf::Sprite &sprite);
            void eventManager(sf::RenderWindow &window, sf::Event &event);
            void setMapSize(sf::Vector2i &size);
            void expulsePlayer(Pex &expulsed_player);
            void playerDeath(Pdi &dead_player);
            bool selectPlayer(sf::Event &event, sf::RenderWindow &window,
                              std::vector<std::string> &command_to_send);
            void deletePlayers();
            void startIncantation(Pic &incantation);
            void endIncantation(Pie &end);

            [[nodiscard]] Player &getSelectedPlayer();
            [[nodiscard]] std::vector<Player> &getPlayers();

        private:
            void depthManager();
            void deselecPlayer(int player_id);
            void verifySounds();

            bool m_player_is_selected = false;
            Player m_selected_player{};
            int m_selected_player_id{};
            std::vector<Player> m_players{};
            std::vector<int> m_elevating_players{};
            sf::Vector2i m_size{};
            sf::SoundBuffer m_death{};
            sf::SoundBuffer m_incantation{};
            sf::SoundBuffer m_success{};
            sf::SoundBuffer m_failure{};
            std::deque<sf::Sound> m_sounds{};
    };
} // namespace zappy
