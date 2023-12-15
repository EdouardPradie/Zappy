/*
** EPITECH PROJECT, 2023
** utils
** File description:
** str_to_word_array
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zappy/server/utils.h>

static int is_delim(char c, const char *delim)
{
    for (int i = 0; delim[i]; i++)
        if (c == delim[i])
            return 1;
    return 0;
}

static int skip_quotes(const char *cmd, char c)
{
    if (!cmd || !(*cmd)) {
        return -1;
    }
    for (unsigned int i = 1; cmd[i]; i += 1)
        if (cmd[i] == c)
            return i;
    return -1;
}

static int count_words(const char *src, char *delim)
{
    int nb = 0;
    int check = 0;

    if (!is_delim(src[0], delim))
        nb++;
    for (int i = 1; src[i]; i++) {
        check = 0;
        if (char_in_str(QUOTATION, src[i])) {
            check = skip_quotes(src + i, src[i]);
            nb++;
        }
        if (check < 0)
            return -1;
        i += check;
        if (!is_delim(src[i], delim) && is_delim(src[i - 1], delim))
            nb++;
    }
    return nb;
}

static int skip_arrline(const char *src, int i, int j, char *delim)
{
    j = i;
    if (char_in_str(QUOTATION, src[i])) {
        j += skip_quotes(src + i, src[i]) + 1;
    } else
        for (j = i; src[j] && !is_delim(src[j], delim); j = j + 1)
            ;
    return j;
}

char **str_to_array(const char *src, char *const delim)
{
    char **array = NULL;
    int nb_words = 0;
    int i = 0;
    int j = 0;

    if (!src || !delim || (nb_words = count_words(src, delim)) <= 0)
        return NULL;
    if (!(array = malloc(sizeof(char *) * (nb_words + 1))))
        return NULL;
    for (int nb = 0; nb < nb_words; nb++) {
        for (i = j; src[i] && is_delim(src[i], delim); i = i + 1)
            ;
        j = skip_arrline(src, i, j, delim);
        if (!(array[nb] = strndup_quotes(src + i, j - i)))
            return NULL;
    }
    array[nb_words] = NULL;
    return array;
}
