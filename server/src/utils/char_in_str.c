/*
** EPITECH PROJECT, 2023
** utils
** File description:
** char_in_str
*/

int char_in_str(const char *const str, char const to_find)
{
    if (!str)
        return 0;
    for (unsigned int i = 0; str[i]; i += 1)
        if (str[i] == to_find)
            return 1;
    return 0;
}
