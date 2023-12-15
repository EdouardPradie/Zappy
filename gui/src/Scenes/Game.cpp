/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Game
*/

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <zappy/GuiCommand/GuiCommand.hh>
#include <zappy/Map/Map.hh>
#include <zappy/MusicManager/MusicManager.hh>
#include <zappy/Player/Player.hh>
#include <zappy/Scenes/Game.hh>

// Constructor && Destructor

zappy::Game::Game(zappy::MusicManager &music_manager) : m_hud{m_player_manager.getPlayers()}, m_music_manager{music_manager}
{
    m_texture.loadFromFile(GAME_TEXTURE.data());
}

// Methods

void zappy::Game::draw(sf::RenderWindow &window)
{
    m_music_manager.fade();
    m_weather.checkWeather(m_music_manager);
    m_sprite.setTexture(m_texture);
    m_map.draw(window, m_sprite);
    m_egg_manager.drawEgg(window, m_sprite, m_player_manager);
    m_player_manager.animatePlayers();
    m_player_manager.drawPlayers(window, m_sprite);
    m_weather.draw(window);
    m_hud.draw(window, m_sprite);
}

void zappy::Game::manageEvent(sf::RenderWindow &window, sf::Event &event,
                              std::vector<std::string> &command_to_send)
{
    bool is_player_selected = m_player_manager.selectPlayer(event, window, command_to_send);
    bool is_tile_selected = m_map.selectTile(event, window);

    m_camera.cameraOnKeyPressed(event);
    m_camera.cameraOnKeyReleased(event);
    m_camera.moveView(window);

    m_hud.eventManager(event, window, command_to_send);
    m_hud.turnHUD(is_player_selected, is_tile_selected);
    if (is_tile_selected)
        m_hud.setFocusedTile(m_map.getSelectedTile());
    if (is_player_selected) {
        m_hud.setFocusedPlayer(m_player_manager.getSelectedPlayer());
        m_map.setCursor(false);
    }
}

void zappy::Game::createMap(zappy::Msz &map, sf::RenderWindow &window)
{
    sf::Vector2i size = {map.x_map_size, map.y_map_size};
    sf::Vector2f center{};
    sf::View window_view = window.getView();

    m_map = zappy::Map{map.x_map_size, map.y_map_size};
    center.x = (map.x_map_size * TILE_SIZE * SCALING) / 2;
    center.y = (map.y_map_size * TILE_SIZE * SCALING) / 2;
    window_view.setCenter(center);
    window.setView(window_view);
    m_player_manager.setMapSize(size);
}

void zappy::Game::changeTileInventory(Bct &tile)
{
    m_map.modifyTile(tile);
}

void zappy::Game::addPlayer(Pnw &new_player)
{
    m_player_manager.addPlayer(new_player);
}

void zappy::Game::changePlayerInventory(Pin &player)
{
    m_player_manager.changePlayerStats(player);
}

void zappy::Game::movePlayer(Ppo &player)
{
    m_player_manager.changePlayerStats(player);
}

void zappy::Game::changePlayerLevel(Plv &player)
{
    m_player_manager.changePlayerStats(player);
}

void zappy::Game::expulsePlayer(Pex &player)
{
    m_player_manager.expulsePlayer(player);
}

void zappy::Game::playerDeath(Pdi &player)
{
    m_player_manager.playerDeath(player);
}

void zappy::Game::startIncantation(Pic &player_incantation)
{
    m_player_manager.startIncantation(player_incantation);
}

void zappy::Game::endIncantation(Pie &player_incantation)
{
    m_player_manager.endIncantation(player_incantation);
}

void zappy::Game::broadcast(Pbc &broadcast)
{
    m_hud.addBroadcast(broadcast);
}

void zappy::Game::eggLayed(Enw &egg_infos)
{
    m_egg_manager.addEggs(egg_infos);
}

void zappy::Game::eggDeath(Edi &egg_infos)
{
    m_egg_manager.eggDeath(egg_infos);
}

void zappy::Game::playerEggConnect(Ebo &egg_selected)
{
    m_egg_manager.eggHatch(egg_selected);
}

void zappy::Game::eggGoingLayed([[maybe_unused]] Pkf &player_layer)
{
}
