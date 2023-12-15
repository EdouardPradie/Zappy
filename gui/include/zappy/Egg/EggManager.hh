/*
** EPITECH PROJECT, 2023
** Egg
** File description:
** EggManager
*/

#pragma once

#include <SFML/System/Clock.hpp>
#include <vector>
#include <zappy/GuiCommand/GuiCommand.hh>
#include <zappy/Player/PlayerManager.hh>

namespace zappy
{
    struct EggInfos {
            bool is_hatching{false};
            bool is_deletable{false};
            bool is_dead{false};
            int egg_number{0};
            int x_tile_coord{0};
            int y_tile_coord{0};
            sf::Clock anim_clock{};
            sf::IntRect rect{176, 56, 32, 48};
            bool wait_idle_anim{false};
            bool reset_hatch_anim{false};
            bool reset_death_anim{false};
    };

    class EggManager
    {
        public:
            EggManager() = default;
            EggManager(EggManager const &to_copy) = default;
            EggManager(EggManager &&to_move) = default;
            ~EggManager() noexcept = default;
            EggManager &operator=(EggManager const &to_copy) = default;
            EggManager &operator=(EggManager &&to_move) = default;

            void eggIdleAnimation(size_t index);
            void eggHatchAnimation(size_t index, zappy::PlayerManager &player_manager);
            void eggDeathAnimation(size_t index);
            void addEggs(Enw &egg_infos);
            void eggHatch(Ebo &egg_selected);
            void eggDeath(Edi &egg_infos);
            void drawEgg(sf::RenderWindow &window, sf::Sprite &sprite,
                         zappy::PlayerManager &player_manager);

        private:
            void deleteUseless();
            std::vector<EggInfos> m_eggs_infos{};
    };
} // namespace zappy
