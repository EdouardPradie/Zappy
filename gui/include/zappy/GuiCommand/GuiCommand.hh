/*
** EPITECH PROJECT, 2023
** GuiCommand
** File description:
** GuiCommand
*/

#pragma once

#include <zappy/Player/Player.hh>
#include <array>

#include <string_view>
#include <variant>

namespace zappy
{
    const constexpr int RESSOURCES_MAX_NB{7};
    const constexpr size_t NB_MAX_CMD{22};

    const constexpr std::array<std::string_view, NB_MAX_CMD> CMD_ARRAY{
        "msz", "bct", "tna", "pnw", "ppo", "plv", "pin", "pex", "pbc", "pic", "pie",
        "pkf", "pdr", "pgt", "pdi", "enw", "ebo", "edi", "sgt", "sst", "seg", "smg"};

    enum class Ressources {
        Food = 0,
        Linemate = 1,
        Deraumede = 2,
        Sibur = 3,
        Menediane = 4,
        Phiras = 5,
        Thystame = 6
    };

    struct Msz {
            int x_map_size{0};
            int y_map_size{0};
            Msz() = default;
    };

    struct Bct {
            int x_tile_coord{0};
            int y_tile_coord{0};
            std::array<int, RESSOURCES_MAX_NB> ressources{};
    };

    struct Tna {
            std::vector<std::string> team_name{};
    };

    struct Pnw {
            short orientation{0};
            short incantation_level{0};
            int player_nb{0};
            int x_tile_coord{0};
            int y_tile_coord{0};
            std::string team_name{};
    };

    struct Ppo {
            int player_nb{0};
            int x_tile_coord{0};
            int y_tile_coord{0};
            zappy::Orientation orientation{0};
    };

    struct Plv {
            int player_nb{0};
            int incantation_level{0};
    };

    struct Pin {
            int player_nb{0};
            int x_tile_coord{0};
            int y_tile_coord{0};
            std::array<int, RESSOURCES_MAX_NB> ressources{};
    };

    struct Pex {
            int player_nb{0};
    };

    struct Pbc {
            int player_nb{0};
            std::string message{};
    };

    struct Pic {
            short incantation_level{0};
            int x_tile_coord{0};
            int y_tile_coord{0};
            std::vector<int> player_list{};
    };

    struct Pie {
            bool result{false};
            int x_tile_coord{0};
            int y_tile_coord{0};
    };

    struct Pkf {
            int player_nb{0};
    };

    struct Pdr {
            int player_nb{0};
            int ressource_nb{0};
    };

    struct Pgt {
            int player_nb{0};
            int ressource_nb{0};
    };

    struct Pdi {
            int player_nb{0};
    };

    struct Enw {
            int egg_number{0};
            int player_nb{0};
            int x_tile_coord{0};
            int y_tile_coord{0};
    };

    struct Ebo {
            int egg_number{0};
    };

    struct Edi {
            int egg_number{0};
    };

    struct Sgt {
            double time_unit{0.00};
    };

    struct Sst {
            double time_unit_modificator{0.00};
    };

    struct Seg {
            std::string team_name{};
    };

    struct Smg {
            std::string servor_message{};
    };

    struct Ukn {
    };

    using Packet = std::variant<Msz, Bct, Tna, Pnw, Ppo, Plv, Pin, Pex, Pbc, Pic, Pie, Pkf, Pdr,
                                Pgt, Pdi, Enw, Ebo, Edi, Sgt, Sst, Seg, Smg, Ukn>;

    struct VariantBind {
            std::string name{};
            zappy::Packet packet;
    };

    static std::array<VariantBind, NB_MAX_CMD> VARIANT_LIST{
        {{"msz", Packet{Msz{}}}, {"bct", Packet{Bct{}}}, {"tna", Packet{Tna{}}},
         {"pnw", Packet{Pnw{}}}, {"ppo", Packet{Ppo{}}}, {"plv", Packet{Plv{}}},
         {"pin", Packet{Pin{}}}, {"pex", Packet{Pex{}}}, {"pbc", Packet{Pbc{}}},
         {"pic", Packet{Pic{}}}, {"pie", Packet{Pie{}}}, {"pkf", Packet{Pkf{}}},
         {"pdr", Packet{Pdr{}}}, {"pgt", Packet{Pgt{}}}, {"pdi", Packet{Pdi{}}},
         {"enw", Packet{Enw{}}}, {"ebo", Packet{Ebo{}}}, {"edi", Packet{Edi{}}},
         {"sgt", Packet{Sgt{}}}, {"sst", Packet{Sst{}}}, {"seg", Packet{Seg{}}},
         {"smg", Packet{Smg{}}}}};

} // namespace zappy
