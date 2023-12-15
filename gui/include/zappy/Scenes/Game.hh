/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Game
*/

#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <string_view>
#include <vector>
#include <zappy/Camera.hh>
#include <zappy/Egg/EggManager.hh>
#include <zappy/GuiCommand/GuiCommand.hh>
#include <zappy/HUD/HUD.hh>
#include <zappy/Map/Map.hh>
#include <zappy/MusicManager/MusicManager.hh>
#include <zappy/ParticleEngine/ParticleEngine.hh>
#include <zappy/Player/Player.hh>
#include <zappy/Player/PlayerManager.hh>
#include <zappy/Scenes/AScene.hh>
#include <zappy/Weather/WeatherManager.hh>

constexpr std::string_view GAME_TEXTURE{"./gui/assets/sprites/Game_texture.png"};

namespace zappy
{
    class Game : public AScene
    {
        public:
            Game(MusicManager &music_manager);
            Game(Game const &to_copy) = delete;
            Game(Game &&to_move) = delete;
            ~Game() override = default;

            Game &operator=(Game const &to_copy) = delete;
            Game &operator=(Game &&to_move) = delete;

            void draw(sf::RenderWindow &window) final;
            void manageEvent(sf::RenderWindow &window, sf::Event &event,
                             std::vector<std::string> &command_to_send) final;

            void createMap(Msz &map, sf::RenderWindow &window);
            void changeTileInventory(Bct &tile);

            void addPlayer(Pnw &new_player);
            void movePlayer(Ppo &player);
            void changePlayerInventory(Pin &player);
            void changePlayerLevel(Plv &player);
            void expulsePlayer(Pex &player);
            void broadcast(Pbc &broadcast);
            void startIncantation(Pic &player_incantation);
            void endIncantation(Pie &player_incantation);
            void eggGoingLayed(Pkf &player_layer);
            void ressourceDropping(Pdr &ressources);
            void ressourceCollecting(Pgt &ressources);
            void playerDeath(Pdi &player);

            void eggLayed(Enw &egg_infos);
            void playerEggConnect(Ebo &egg_selected);
            void eggDeath(Edi &egg_infos);

            void getTimeUnit(Sgt &time_unit);
            void getTimeUnitModifier(Sst &time_unit_modifier);

            void winTeam(Seg &winner);

            void servorMsg(Smg &message);

        private:
            zappy::PlayerManager m_player_manager;
            zappy::HUD m_hud;
            zappy::Map m_map;
            zappy::Camera m_camera;
            zappy::MusicManager &m_music_manager;
            zappy::WeatherManager m_weather;

            sf::Sound m_sound;
            zappy::EggManager m_egg_manager{};
            int m_test_flag{0};
    };
} // namespace zappy
