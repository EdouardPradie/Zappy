/*
** EPITECH PROJECT, 2023
** utils
** File description:
** array_len
*/

#include <sys/types.h>

ssize_t array_len(void *const to_size)
{
    void **arr = (void **)to_size;
    ssize_t ind = 0;

    if (!arr)
        return -1;
    while (arr[ind])
        ind++;
    return ind;
}
