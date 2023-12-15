/*
** EPITECH PROJECT, 2023
** load
** File description:
** tests_arguments
*/

#include <criterion/criterion.h>
#include <criterion/internal/redirect.h>
#include <criterion/internal/test.h>
#include <zappy/config/arguments.h>
#include <zappy/server.h>

void redirect(void);

Test(parse_args, basic_test)
{
    args_config_t args = {0};
    char *const argv[] = {"i"};

    cr_assert_eq(parse_args(&args, 1, argv), SUCCESS);
    cr_assert_eq(args.port, 4242);
    cr_assert_eq(args.nb_clients_og, DEFAULT_CLIENTS);
}

Test(parse_args, basic_test_null)
{
    args_config_t args = {0};
    char *const argv[] = {"i"};

    cr_assert_eq(parse_args(NULL, 1, argv), FAILURE);
    cr_assert_eq(parse_args(&args, 1, NULL), FAILURE);
}

Test(parse_args, no_port, .init = redirect)
{
    args_config_t args = {0};
    char *const argv[] = {"i", "-p"};

    cr_assert_eq(parse_args(&args, 2, argv), FAILURE);
    cr_assert_stderr_eq_str("i: option requires an argument -- 'p'\n");
}

Test(parse_args, invalid_port, .init = redirect)
{
    args_config_t args = {0};
    char *const arg2[] = {"i", "-p", "abc"};

    cr_assert_eq(parse_args(&args, 3, arg2), FAILURE);
    cr_assert_stderr_eq_str(ERROR_PORT);
}

Test(parse_args, no_width, .init = redirect)
{
    args_config_t args = {0};
    char *const arg1[] = {"i", "-x"};

    cr_assert_eq(parse_args(&args, 2, arg1), FAILURE);
    cr_assert_stderr_eq_str("i: option requires an argument -- 'x'\n");
}

Test(parse_args, invalid_width, .init = redirect)
{
    args_config_t args = {0};
    char *const arg2[] = {"i", "-x", "abc"};

    cr_assert_eq(parse_args(&args, 3, arg2), FAILURE);
    cr_assert_stderr_eq_str(ERROR_WIDTH);
}

Test(parse_args, no_height, .init = redirect)
{
    args_config_t args = {0};
    char *const arg1[] = {"i", "-y"};

    cr_assert_eq(parse_args(&args, 2, arg1), FAILURE);
    cr_assert_stderr_eq_str("i: option requires an argument -- 'y'\n");
}

Test(parse_args, invalid_height, .init = redirect)
{
    args_config_t args = {0};
    char *const arg2[] = {"i", "-y", "abc"};

    cr_assert_eq(parse_args(&args, 3, arg2), FAILURE);
    cr_assert_stderr_eq_str(ERROR_HEIGHT);
}

Test(parse_args, no_teams, .init = redirect)
{
    args_config_t args = {0};
    char *const arg1[] = {"i", "-n"};

    cr_assert_eq(parse_args(&args, 2, arg1), FAILURE);
    cr_assert_stderr_eq_str("i: option requires an argument -- 'n'\n");
}

Test(parse_args, invalid_teams, .init = redirect)
{
    args_config_t args = {0};
    char *const arg2[] = {"i", "-n", "abc", "abc"};

    cr_assert_eq(parse_args(&args, 4, arg2), FAILURE);
    cr_assert_stderr_eq_str(ERROR_TEAM_NAME);
}

Test(parse_args, no_client_nb, .init = redirect)
{
    args_config_t args = {0};
    char *const arg1[] = {"i", "-c"};

    cr_assert_eq(parse_args(&args, 2, arg1), FAILURE);
    cr_assert_stderr_eq_str("i: option requires an argument -- 'c'\n");
}

Test(parse_args, invalid_client_nb, .init = redirect)
{
    args_config_t args = {0};
    char *const arg2[] = {"i", "-c", "abc"};

    cr_assert_eq(parse_args(&args, 3, arg2), FAILURE);
    cr_assert_stderr_eq_str(ERROR_CLIENTS);
}
