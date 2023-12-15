/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Player
*/

#pragma once

#include <Inventory.hh>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace zappy
{

    enum class Orientation {
        North = 1,
        East = 2,
        South = 3,
        West = 4,
    };

    struct PlayerInfo {
            int m_id;
            int m_level;
            float m_x;
            float m_y;
            Orientation m_orientation;
            std::string m_team;
    };

    class Player
    {
        public:
            Player() = default;
            Player(const PlayerInfo &infos);
            Player(Player const &to_copy) = default;
            Player(Player &&to_move) = default;
            ~Player() = default;

            Player &operator=(Player const &to_copy) = default;
            Player &operator=(Player &&to_move) = default;

            void movePlayer(int pos_x, int pos_y, Orientation orientation);
            void animatePlayer(sf::Vector2i &size);
            void drawPlayer(sf::RenderWindow &window, sf::Sprite &sprite, sf::Vector2i &size);
            void setPlayerLevel(int level);
            void setPlayerInventory(Inventory &inventory);
            void triggerDeath();
            void triggerSelection(bool status);
            void triggerExpulse();
            void triggerElevation(bool status);

            [[nodiscard]] int getId() const;
            [[nodiscard]] sf::Vector2f getWorldPosition() const;
            [[nodiscard]] sf::Vector2i getLocalPosition() const;
            [[nodiscard]] Inventory getInventory() const;
            [[nodiscard]] bool canDeletePlayer() const;
            [[nodiscard]] sf::FloatRect getColliderBox() const;
            [[nodiscard]] const std::string &getTeam() const;
            [[nodiscard]] int getLevel() const;
            [[nodiscard]] bool getDeathStatus() const;

        private:
            int m_id{};
            int m_level{};
            Orientation m_orientation{};
            sf::Clock m_clock{};
            sf::Vector2i m_position{};
            sf::Vector2f m_remain{};
            sf::Vector2f m_position_map{};
            sf::IntRect m_rect{};
            sf::FloatRect m_box{};
            Inventory m_inventory{};
            std::string m_team{};
            void animateNorth(sf::Vector2i &size);
            void animateEast(sf::Vector2i &size);
            void animateSouth(sf::Vector2i &size);
            void animateWest(sf::Vector2i &size);
            void checkBoundaries(sf::Vector2i &size);
            void animateDeath();
            void expulsedNorth();
            void expulsedEast();
            void expulsedSouth();
            void expulsedWest();
            void animateSelected();
            void playerMovement();
            void animateElevation();

            bool m_is_dead = false;
            bool m_delete = false;
            bool m_selected = false;
            bool m_spark = true;
            bool m_expulse = false;
            bool m_elevate = false;

            sf::Clock m_clock_selected{};
            sf::Color m_color = {255, 255, 255};
    };
} // namespace zappy
