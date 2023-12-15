/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** HUD
*/

#pragma once

#include <vector>
#include <zappy/HUD/SelectionPanel.hh>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <array>
#include <ctime>
#include <deque>
#include <string>
#include <string_view>
#include <vector>
#include <zappy/GuiCommand/GuiCommand.hh>
#include <zappy/HUD/FrequencyPanel.hh>
#include <zappy/Map/Tile.hh>
#include <zappy/Player/Player.hh>

constexpr std::string_view MAIN_FONT{"./gui/assets/fonts/botw.otf"};
constexpr std::string_view BROADCAST_SOUND{"./gui/assets/sound/announcement.ogg"};
constexpr std::string_view LINEMATE{"Linemate"};
constexpr std::string_view DERAUMEDE{"Deraumede"};
constexpr std::string_view SIBUR{"Sibur"};
constexpr std::string_view MENDIANE{"Mendiane"};
constexpr std::string_view PHIRAS{"Phiras"};
constexpr std::string_view THYSTAME{"Thystame"};

constexpr int HUD_WIDTH{330};
constexpr int HUD_HEIGHT{56};
constexpr int HUD_LIMIT{360 * 2};
constexpr int HUD_SPEED{10};

constexpr int MAX_ALPHA{255};
constexpr int MIN_ALPHA{100};
constexpr int ALPHA_SPEED{15};

constexpr int RUPEE_WIDTH{10};
constexpr int RUPEE_HEIGHT{15};
constexpr int RUPEE_TYPES{6};
constexpr int RUPEE_PHASES{6};
constexpr float RUPEE_COUNTDOWN_1{75};
constexpr float RUPEE_COUNTDOWN_2{2};

namespace zappy
{
    class HUD
    {
        public:
            HUD(std::vector<Player> &players);
            HUD(HUD const &to_copy) = default;
            HUD(HUD &&to_move) = default;
            ~HUD() = default;

            HUD &operator=(HUD const &to_copy) = delete;
            HUD &operator=(HUD &&to_move) = delete;

            void draw(sf::RenderWindow &window, sf::Sprite &sprite);
            void displayFocusedTile(zappy::Tile &focused_tile);
            void setFocusedTile(zappy::Tile &tile);
            void setFocusedPlayer(zappy::Player &player);
            void eventManager(sf::Event &event, sf::RenderWindow &window,
                              std::vector<std::string> &command_to_send);
            void turnHUD(bool status1, bool status2);
            void addBroadcast(Pbc &broadcast);

        private:
            void initializeParchment();
            void initializeRupees();
            void initializeTexts();
            void initializeFood();
            void initializeBroadcastView();
            void animateHUD();
            void animateRupees();
            void animateFood();
            void animateBroadcast();
            void resetBroadcast();

            void drawTexts(sf::RenderWindow &window);
            void drawSprites(sf::RenderWindow &window, sf::Sprite &sprite);

            sf::View m_hud_view{};
            sf::View m_broadcast_view{};
            sf::Vector2f m_hud_scale{};
            sf::SoundBuffer m_broadcast{};
            sf::Sound m_sound_broadcast{};
            bool m_is_active{false};
            bool m_is_faded{false};
            int m_rupees_phases{0};
            int m_food_phases{0};

            sf::Text m_text{};
            sf::Font m_font{};
            sf::Color m_color{};
            sf::Color m_color_text{31, 31, 31, 255};
            sf::Clock m_rupees_clock{};
            sf::Clock m_food_clock{};
            sf::Clock m_broadcast_clock{};

            zappy::Tile m_parchment{};
            zappy::Tile m_food{};
            zappy::Text m_title{};
            zappy::Text m_food_text{};
            zappy::Text m_food_count{};
            zappy::FrequencyPanel m_frequency_panel{};
            zappy::SelectionPanel m_selection_panel;
            std::vector<Text> m_broadcast_messages{};
            std::array<Tile, 6> m_rupees{};
            std::array<Text, 6> m_texts{};
            std::array<Text, 6> m_ressources{};
    };
} // namespace zappy
