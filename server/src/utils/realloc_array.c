/*
** EPITECH PROJECT, 2023
** utils
** File description:
** concat_arrays
*/

#include <stdlib.h>
#include <string.h>
#include <zappy/server/utils.h>

char **realloc_array(char **ptr, u_int y, u_int x)
{
    char **new_ptr = NULL;
    u_int i = 0;

    new_ptr = malloc(sizeof(char *) * (y + 1));
    if (!new_ptr)
        return NULL;
    for (i = 0; ptr && ptr[i]; i++)
        new_ptr[i] = ptr[i];
    for (; i < y; i++) {
        if (!(new_ptr[i] = malloc(sizeof(char) * (x + 1))))
            return NULL;
        memset(new_ptr[i], '\0', x);
    }
    new_ptr[y] = NULL;
    free(ptr);
    return new_ptr;
}
