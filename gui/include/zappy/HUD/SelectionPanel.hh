/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** SelectionPanel
*/

#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <zappy/Map/Tile.hh>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <zappy/Player/Player.hh>
#include <vector>

namespace zappy
{

    struct SelectionTile {
        sf::FloatRect m_box{};
        sf::Vector2f m_position{};
        sf::Color m_color{209, 186, 159};
        bool m_selected{};
    };

    class SelectionPanel
    {
        public:
            SelectionPanel(std::vector<Player> &m_players);
            SelectionPanel(SelectionPanel const &to_copy) = default;
            SelectionPanel(SelectionPanel &&to_move) = default;
            ~SelectionPanel() noexcept = default;

            SelectionPanel &operator=(SelectionPanel const &to_copy) = delete;
            SelectionPanel &operator=(SelectionPanel &&to_move) = delete;

            void draw(sf::RenderWindow &window, sf::Sprite &sprite, sf::Text &text);
            void manageEvent(sf::RenderWindow &window, sf::Event &event);

            [[nodiscard]] bool isPlayerSelected() const;
            [[nodiscard]] Player &getSelectedPlayer() const;

        private:
            void animatePanel();
            void checkSelection(sf::RenderWindow &window, sf::Event &event);
            void updateShapes();
            void resetSelection();

            sf::Clock m_clock;
            sf::View m_view;
            sf::Vector2f m_standard_sprite;
            sf::Vector2f m_standard_id;
            sf::Vector2f m_standard_team;
            sf::Vector2f m_standard_position;
            sf::Vector2f m_global_position;
            sf::Vector2f m_standard_rect;
            sf::Vector2f m_last;
            sf::RectangleShape m_shape;

            bool m_is_active{false};
            bool m_is_selected{false};
            size_t m_selection_id{0};
            Tile m_panel;
            std::vector<Player> &m_players;
            std::vector<SelectionTile> m_tiles;
    };

} // namespace zappy
