/*
** EPITECH PROJECT, 2023
** tests
** File description:
** tests_utils
*/

#include <criterion/criterion.h>
#include <criterion/internal/redirect.h>
#include <zappy/server.h>
#include <zappy/server/utils.h>

void redirect(void);

Test(array_len, array_len)
{
    char **arr = str_to_array("ouinouinouin", "n");

    cr_assert_eq(array_len(NULL), -1);
    cr_assert_eq(array_len(arr), 3);
    free_array(arr);
}

Test(char_in_str, char_in_str)
{
    cr_assert_eq(char_in_str("ouin", 'i'), true);
    cr_assert_eq(char_in_str("ouin", 'z'), false);
    cr_assert_eq(char_in_str(NULL, 'z'), false);
}

Test(print_help, print_help, .init = redirect)
{
    cr_assert_eq(print_help(98), 98);
    cr_assert_stdout_eq_str(HELP);
}

Test(generate_uuid, generate_uuid)
{
    char *unparse = generate_uuid();

    cr_assert_not_null(unparse);
    free(unparse);
}

Test(set_error, set_error)
{
    cr_assert_eq(set_error(1, NULL, false), FAILURE);
}

Test(strisnum, strisnum)
{
    cr_assert_eq(strisnum(NULL), false);
}
