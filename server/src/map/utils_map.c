/*
** EPITECH PROJECT, 2023
** map
** File description:
** utils_map
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/map_utils.h>

int stock(vector2i_t size, double density, int *stock_left)
{
    int div = ceil(size.x * size.y * density / (*stock_left));
    int res = 0;

    if (*stock_left <= 0)
        return 0;
    if (div > *stock_left)
        div = *stock_left;
    if (div <= 1)
        div = 2;
    res = rand() % div;
    (*stock_left) -= res;
    return res;
}

bool has_stock_left(const int *stock)
{
    for (u_int i = 0; i < INVENTORY_SLOTS; i++) {
        if (stock[i] > 0)
            return true;
    }
    return false;
}

int len_eggs(const int *src)
{
    int size = 0;

    if (!src)
        return -1;
    while (src[size] != -1)
        size++;
    return size;
}
