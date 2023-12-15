/*
** EPITECH PROJECT, 2023
** utils
** File description:
** delete_from_array
*/

#include <stdlib.h>
#include <zappy/server/utils.h>

char **delete_from_array(char **src, u_int ind)
{
    ssize_t size = 0;
    char **dest = NULL;
    int flag = 0;

    if (!src || (size = array_len(src)) < ind)
        return NULL;
    if (!(dest = malloc(sizeof(char *) * (size))))
        return NULL;
    dest[size] = NULL;
    for (u_int i = 0; i < size - 1; i++) {
        if (i == ind)
            flag = 1;
        dest[i] = src[i + flag];
    }
    free(src);
    return dest;
}
