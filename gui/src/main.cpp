/*
** EPITECH PROJECT, 2023
** src
** File description:
** main
*/

#include <cstdlib>
#include <iostream>
#include <zappy/GUI/GUI.hh>
#include <zappy/ZappyError.hh>
#include <zappy/gui.hh>

int main(int argc, const char *argv[])
{
    if (argc != 3)
        return FAILURE;
    try {
        zappy::GUI gui{argv[1], static_cast<unsigned short>(std::atoi(argv[2]))};
        gui.start();
    } catch (zappy::ZappyException &e) {
        std::cout << e.what();
        return FAILURE;
    }
    return SUCCESS;
}
