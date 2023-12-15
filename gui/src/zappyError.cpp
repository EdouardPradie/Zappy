/*
** EPITECH PROJECT, 2023
** src
** File description:
** zappyError
*/

#include <zappy/ZappyError.hh>

[[nodiscard]] const char *zappy::ZappyException::what() const noexcept
{
    return error_msg.c_str();
}
