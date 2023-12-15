/*
** EPITECH PROJECT, 2023
** utils
** File description:
** free_array
*/

#include <stdlib.h>

void free_array(void *to_del)
{
    void **arr = (void **)to_del;

    if (!arr || !(*arr))
        return;
    for (unsigned int i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}
