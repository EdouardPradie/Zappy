/*
** EPITECH PROJECT, 2023
** utils
** File description:
** strisnum
*/

#include <stdbool.h>

bool strisnum(const char *const str)
{
    if (!str)
        return false;
    for (int i = 0; str[i]; i++) {
        if (str[i] >= '0' && str[i] <= '9')
            continue;
        return false;
    }
    return true;
}
