/*
** EPITECH PROJECT, 2023
** GuiClient
** File description:
** GuiClient
*/

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Socket.hpp>
#include <SFML/System/Clock.hpp>
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <zappy/GuiClient/GuiClient.hpp>
#include <zappy/GuiCommand/GuiCommand.hh>
#include <zappy/Player/Player.hh>
#include <zappy/Scenes/Game.hh>
#include <zappy/Scenes/SceneManager.hh>
#include <zappy/Scenes/Victory.hh>
#include <zappy/ZappyError.hh>

zappy::Client::Client(const std::string &name, unsigned short port)
{
    if (m_socket.connect(sf::IpAddress{name}, port) != sf::Socket::Status::Done)
        throw zappy::ZappyException{"cant connect to server\n"};
    m_socket.setBlocking(false);
}

void zappy::Client::sendCommand(const std::string &cmd)
{
    const char *data_ptr = cmd.c_str();
    std::size_t data_size = cmd.size();
    std::size_t total_sent = 0;

    while (total_sent < data_size) {
        std::size_t sent = 0;
        m_status = m_socket.send(data_ptr + total_sent, data_size - total_sent, sent);
        if (m_status == sf::Socket::Error || m_status == sf::Socket::Disconnected)
            return;
        total_sent += sent;
    }
}

void zappy::Client::sendGraphic()
{
    sendCommand("GRAPHIC\n");
}

bool zappy::Client::WelcomeSuppressor()
{
    char buff[4096] = {0}; // NOLINT
    std::size_t size;
    sf::Clock clk{};

    while (clk.getElapsedTime().asSeconds() < 20) {
        if (m_socket.receive(&buff, 4096, size) != sf::Socket::Done)
            return true;
    }
    throw zappy::ZappyException{"Server do not send Welcome in time\n"};
}

static std::vector<std::string> parser(const std::string &buff)
{
    std::vector<std::string> parsed{};
    std::istringstream stringstream{buff};
    std::string token;

    while (std::getline(stringstream, token, ' '))
        parsed.emplace_back(token);
    return parsed;
}

static zappy::Packet get_variant(std::vector<std::string> &parsed)
{
    if (parsed.empty())
        return zappy::Packet{zappy::Ukn{}};
    for (size_t i{0}; i < zappy::NB_MAX_CMD; i++) {
        if (parsed[0] == zappy::VARIANT_LIST[i].name)
            return zappy::VARIANT_LIST[i].packet;
    }
    return zappy::Packet{zappy::Ukn{}};
}

void zappy::Client::receiveCommand(zappy::SceneManager &scene_manager, sf::RenderWindow &window)
{
    char buff[255] = {0}; // NOLINT
    std::size_t index{0};
    char tmp = -1;

    fillRingBuffer();
    std::memset(buff, '\0', 255);
    while ((tmp = m_ring_buffer.front()) != '\0') {
        if (m_ring_buffer.isWritable()) {
            if (!fillRingBuffer()) {
                m_ring_buffer.clear();
                return;
            }
            buff[index] = tmp;
            index += 1;
        } else if (tmp == '\n') {
            applyCommands(scene_manager, window, std::string{buff});
            index = 0;
            std::memset(buff, '\0', 255);
        } else {
            buff[index] = tmp;
            index += 1;
        }
    }
    m_ring_buffer.clear();
}

bool zappy::Client::fillRingBuffer()
{
    char buffer[1364]; // NOLINT
    std::size_t size{1364};
    std::size_t read_size{0};

    std::memset(buffer, '\0', 1364);
    m_socket.receive(buffer, size, read_size);
    if (size == 0)
        return false;
    for (auto chr : buffer)
        m_ring_buffer.push(chr);
    return true;
}

void zappy::Client::applyCommands(zappy::SceneManager &scene_manager, sf::RenderWindow &window,
                                  const std::string &str)
{
    std::vector<std::string> parsed;
    parsed = parser(str);
    Packet variant = get_variant(parsed);
    auto *game = dynamic_cast<Game *>(scene_manager.getScenes()[1].get());
    if (!game)
        throw ZappyException{"dynamic_cast error\n"};
    auto *victory = dynamic_cast<Victory *>(scene_manager.getScenes()[2].get());
    if (!victory)
        throw ZappyException{"dynamic_cast error\n"};
    auto visitor = make_lambda_visitor(
        [&](Msz &arg) {
            arg.x_map_size = std::atoi(parsed[1].c_str());
            arg.y_map_size = std::atoi(parsed[2].c_str());
            game->createMap(arg, window);
        },
        [&](Bct &arg) {
            arg.x_tile_coord = std::atoi(parsed[1].c_str());
            arg.y_tile_coord = std::atoi(parsed[2].c_str());
            arg.ressources[0] = std::atoi(parsed[3].c_str());
            arg.ressources[1] = std::atoi(parsed[4].c_str());
            arg.ressources[2] = std::atoi(parsed[5].c_str());
            arg.ressources[3] = std::atoi(parsed[6].c_str());
            arg.ressources[4] = std::atoi(parsed[7].c_str());
            arg.ressources[5] = std::atoi(parsed[8].c_str());
            arg.ressources[6] = std::atoi(parsed[9].c_str());
            game->changeTileInventory(arg);
        },
        [&](Tna &arg) {
            for (size_t i{1}; i < parsed.size(); i++)
                arg.team_name.push_back(parsed[i]);
        },
        [&](Pnw &arg) {
            arg.player_nb = std::atoi(parsed[1].c_str());
            arg.x_tile_coord = std::atoi(parsed[2].c_str());
            arg.y_tile_coord = std::atoi(parsed[3].c_str());
            arg.orientation = static_cast<short>(std::atoi(parsed[4].c_str()));
            arg.incantation_level = static_cast<short>(std::atoi(parsed[5].c_str()));
            arg.team_name = parsed[6];
            game->addPlayer(arg);
        },
        [&](Ppo &arg) {
            arg.player_nb = std::atoi(parsed[1].c_str());
            arg.x_tile_coord = std::atoi(parsed[2].c_str());
            arg.y_tile_coord = std::atoi(parsed[3].c_str());
            arg.orientation = static_cast<Orientation>(std::atoi(parsed[4].c_str()));
            game->movePlayer(arg);
        },
        [&](Plv &arg) {
            arg.player_nb = std::atoi(parsed[1].c_str());
            arg.incantation_level = std::atoi(parsed[2].c_str());
            game->changePlayerLevel(arg);
        },
        [&](Pin &arg) {
            arg.player_nb = std::atoi(parsed[1].c_str());
            arg.x_tile_coord = std::atoi(parsed[2].c_str());
            arg.y_tile_coord = std::atoi(parsed[3].c_str());
            arg.ressources[0] = std::atoi(parsed[4].c_str());
            arg.ressources[1] = std::atoi(parsed[5].c_str());
            arg.ressources[2] = std::atoi(parsed[6].c_str());
            arg.ressources[3] = std::atoi(parsed[7].c_str());
            arg.ressources[4] = std::atoi(parsed[8].c_str());
            arg.ressources[5] = std::atoi(parsed[9].c_str());
            arg.ressources[6] = std::atoi(parsed[10].c_str());
            game->changePlayerInventory(arg);
        },
        [&](Pex &arg) {
            arg.player_nb = std::atoi(parsed[1].c_str());
            game->expulsePlayer(arg);
        },
        [&](Pbc &arg) {
            arg.player_nb = std::atoi(parsed[1].c_str());
            for (size_t iterator = 2; iterator < parsed.size(); iterator += 1)
                arg.message += parsed[iterator] + " ";
            game->broadcast(arg);
        },
        [&](Pic &arg) {
            arg.x_tile_coord = std::atoi(parsed[1].c_str());
            arg.y_tile_coord = std::atoi(parsed[2].c_str());
            arg.incantation_level = static_cast<short>(std::atoi(parsed[3].c_str()));
            for (size_t i{4}; i < parsed.size(); i++)
                arg.player_list.push_back(std::atoi(parsed[i].c_str()));
            game->startIncantation(arg);
        },
        [&](Pie &arg) {
            arg.x_tile_coord = std::atoi(parsed[1].c_str());
            arg.y_tile_coord = std::atoi(parsed[2].c_str());
            arg.result = std::atoi(parsed[3].c_str());
            game->endIncantation(arg);
        },
        [&](Pkf &arg) {
            arg.player_nb = std::atoi(parsed[1].c_str());
            game->eggGoingLayed(arg);
        },
        [&](Pdr &arg) {
            arg.player_nb = std::atoi(parsed[1].c_str());
            arg.ressource_nb = std::atoi(parsed[2].c_str());
            // game.ressourceDropping(arg);
        },
        [&](Pgt &arg) {
            arg.player_nb = std::atoi(parsed[1].c_str());
            arg.ressource_nb = std::atoi(parsed[2].c_str());
            // game.ressourceCollecting(arg);
        },
        [&](Pdi &arg) {
            arg.player_nb = std::atoi(parsed[1].c_str());
            game->playerDeath(arg);
        },
        [&](Enw &arg) {
            arg.egg_number = std::atoi(parsed[1].c_str());
            arg.player_nb = std::atoi(parsed[2].c_str());
            arg.x_tile_coord = std::atoi(parsed[3].c_str());
            arg.y_tile_coord = std::atoi(parsed[4].c_str());
            game->eggLayed(arg);
        },
        [&](Ebo &arg) {
            arg.egg_number = std::atoi(parsed[1].c_str());
            game->playerEggConnect(arg);
        },
        [&](Edi &arg) {
            arg.egg_number = std::atoi(parsed[1].c_str());
            game->eggDeath(arg);
        },
        [&](Ukn & /*arg*/) { return; },
        [&](Sgt &arg) {
            arg.time_unit = std::atoi(parsed[1].c_str());
            // game->getTimeUnit(arg);
        },
        [&](Sst &arg) {
            arg.time_unit_modificator = std::atof(parsed[1].c_str());
            // game.getTimeUnitModifier(arg);
        },
        [&](Seg &arg) {
            arg.team_name = parsed[1];
            victory->setVictoryTeam(arg.team_name);
            scene_manager.changeScene(2);
        },
        [&](Smg &arg) {
            arg.servor_message = parsed[1];
            // game.servorMsg(arg);
        });
    std::visit(visitor, variant);
}

sf::Socket::Status zappy::Client::getSocketStatus() const
{
    return m_status;
}
