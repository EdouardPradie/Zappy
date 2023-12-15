/*
** EPITECH PROJECT, 2023
** gui
** File description:
** PlayerManager
*/

#include <Inventory.hh>
#include <SFML/Audio/Sound.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <ios>
#include <string>
#include <vector>
#include <zappy/GuiCommand/GuiCommand.hh>
#include <zappy/Player/Player.hh>
#include <zappy/Player/PlayerManager.hh>

// Constructor && Destructor

zappy::PlayerManager::PlayerManager()
{
    m_death.loadFromFile(DEATH_SOUND.data());
    m_incantation.loadFromFile(INCANTATION_SOUND.data());
    m_failure.loadFromFile(INCANTATION_SUCCESS.data());
    m_success.loadFromFile(INCANTATION_FAILED.data());
}

// Methods

void zappy::PlayerManager::animatePlayers()
{
    depthManager();
    verifySounds();
    for (auto &player : m_players)
        player.animatePlayer(m_size);
    deletePlayers();
}

void zappy::PlayerManager::depthManager()
{
    auto compare = [](Player &player_a, Player &player_b) {
        return player_a.getLocalPosition().y < player_b.getLocalPosition().y;
    };
    std::sort(m_players.begin(), m_players.end(), compare);
}

void zappy::PlayerManager::drawPlayers(sf::RenderWindow &window, sf::Sprite &sprite)
{
    for (auto &player : m_players)
        player.drawPlayer(window, sprite, m_size);
}

void zappy::PlayerManager::setMapSize(sf::Vector2i &size)
{
    m_size = size;
}

void zappy::PlayerManager::changePlayerStats(zappy::Ppo &position)
{
    for (auto &player : m_players) {
        if (player.getId() == position.player_nb) {
            player.movePlayer(position.x_tile_coord, position.y_tile_coord, position.orientation);
            break;
        }
    }
}

void zappy::PlayerManager::changePlayerStats(zappy::Plv &level)
{
    for (auto &player : m_players) {
        if (player.getId() == level.player_nb) {
            player.setPlayerLevel(level.incantation_level);
            break;
        }
    }
}

void zappy::PlayerManager::changePlayerStats(zappy::Pin &inventory)
{
    Inventory p_inventory = {0};

    p_inventory.food = static_cast<unsigned int>(inventory.ressources[0]);
    p_inventory.linemate = static_cast<unsigned int>(inventory.ressources[1]);
    p_inventory.deraumede = static_cast<unsigned int>(inventory.ressources[2]);
    p_inventory.sibur = static_cast<unsigned int>(inventory.ressources[3]);
    p_inventory.mendiane = static_cast<unsigned int>(inventory.ressources[4]);
    p_inventory.phiras = static_cast<unsigned int>(inventory.ressources[5]);
    p_inventory.thystame = static_cast<unsigned int>(inventory.ressources[6]);
    for (auto &player : m_players) {
        if (player.getId() == inventory.player_nb) {
            player.setPlayerInventory(p_inventory);
            break;
        }
    }
}

void zappy::PlayerManager::addPlayer(Pnw &new_player)
{
    PlayerInfo infos{new_player.player_nb,
                     new_player.incantation_level,
                     static_cast<float>(new_player.x_tile_coord),
                     static_cast<float>(new_player.y_tile_coord),
                     static_cast<Orientation>(new_player.orientation),
                     new_player.team_name};
    m_players.emplace_back(infos);
}

void zappy::PlayerManager::expulsePlayer(Pex &expulsed_player)
{
    Player expulser;
    sf::Vector2i expulser_position;
    sf::Vector2i position;

    for (auto &player : m_players) {
        if (player.getId() == expulsed_player.player_nb) {
            expulser = player;
            break;
        }
    }
    expulser_position = expulser.getLocalPosition();
    for (auto &player : m_players) {
        position = player.getLocalPosition();
        if (position == expulser_position && expulser.getId() != player.getId())
            player.triggerExpulse();
    }
}

void zappy::PlayerManager::playerDeath(Pdi &dead_player)
{
    for (auto &player : m_players) {
        if (player.getId() == dead_player.player_nb && !player.getDeathStatus()) {
            m_sounds.emplace_front();
            auto sound = m_sounds.begin();
            sound->setBuffer(m_death);
            sound->setVolume(100.F);
            sound->play();
            player.triggerDeath();
            break;
        }
    }
}

void zappy::PlayerManager::deletePlayers()
{
    for (auto iterator = m_players.cbegin(); iterator != m_players.cend(); iterator++) {
        if (iterator->canDeletePlayer()) {
            m_players.erase(iterator);
            break;
        }
    }
}

bool zappy::PlayerManager::selectPlayer(sf::Event &event, sf::RenderWindow &window,
                                        std::vector<std::string> &command_to_send)
{
    sf::Vector2i tmp{event.mouseButton.x, event.mouseButton.y};
    const sf::Vector2f point = window.mapPixelToCoords(tmp);
    bool is_touched = false;

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        for (auto &player : m_players) {
            if (player.getColliderBox().contains(point)) {
                deselecPlayer(m_selected_player_id);
                m_player_is_selected = true;
                m_selected_player_id = player.getId();
                command_to_send.emplace_back("pin " + std::to_string(player.getId()) + "\n");
                command_to_send.emplace_back("plv " + std::to_string(player.getId()) + "\n");
                m_selected_player = player;
                player.triggerSelection(true);
                is_touched = true;
                break;
            }
        }
        if (!is_touched) {
            m_player_is_selected = false;
            deselecPlayer(m_selected_player_id);
        }
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        m_player_is_selected = false;
        deselecPlayer(m_selected_player_id);
    }
    return m_player_is_selected;
}

void zappy::PlayerManager::deselecPlayer(int player_id)
{
    for (auto &player : m_players) {
        if (player.getId() == player_id)
            player.triggerSelection(false);
    }
}

zappy::Player &zappy::PlayerManager::getSelectedPlayer()
{
    return m_selected_player;
}

void zappy::PlayerManager::startIncantation(Pic &incantation)
{
    m_sounds.emplace_front();
    auto sound = m_sounds.begin();
    sound->setBuffer(m_incantation);
    sound->setVolume(100.F);
    sound->play();
    for (auto &player : m_players) {
        for (auto &identity : incantation.player_list)
            if (player.getId() == identity) {
                player.triggerElevation(true);
                m_elevating_players.emplace_back(player.getId());
            }
    }
}

void zappy::PlayerManager::endIncantation(Pie &end)
{
    sf::Vector2i position{end.x_tile_coord, end.y_tile_coord};

    m_sounds.emplace_front();
    auto sound = m_sounds.begin();
    if (end.result == 0)
        sound->setBuffer(m_failure);
    else
        sound->setBuffer(m_success);
    sound->setVolume(100.F);
    sound->play();
    for (auto &player : m_players) {
        for (auto iterator = m_elevating_players.begin(); iterator != m_elevating_players.end();) {
            if (player.getId() == *iterator && player.getLocalPosition() == position) {
                player.triggerElevation(false);
                iterator = m_elevating_players.erase(iterator);
            } else
                iterator += 1;
        }
    }
}

void zappy::PlayerManager::verifySounds()
{
    for (auto iterator = m_sounds.begin(); iterator != m_sounds.end();) {
        if (iterator->getStatus() == sf::Sound::Stopped)
            iterator = m_sounds.erase(iterator);
        else
            iterator++;
    }
}

std::vector<zappy::Player> &zappy::PlayerManager::getPlayers()
{
    return m_players;
}
