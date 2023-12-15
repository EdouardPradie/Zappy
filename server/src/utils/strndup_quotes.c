/*
** EPITECH PROJECT, 2023
** utils
** File description:
** strndup_quotes
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *strndup_quotes(const char *src, size_t n)
{
    char *dest = NULL;

    if (src[0] == '"') {
        src++;
        n -= 2;
    }
    dest = strndup(src, n);
    return dest;
}
