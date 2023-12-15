/*
** EPITECH PROJECT, 2023
** load
** File description:
** test_arguments_ptr
*/

#include <criterion/criterion.h>
#include <criterion/internal/redirect.h>
#include <criterion/internal/test.h>
#include <unistd.h>
#include <zappy/config/arguments.h>
#include <zappy/server.h>
#include <zappy/server/utils.h>

void redirect(void);

// p handler
Test(p_handler, valid_p_handler)
{
    args_config_t args = {0};
    optarg = "4242";

    cr_assert_eq(p_handler(&args, NULL, 0), SUCCESS);
}

Test(p_handler, p_handler_negative, .init = redirect)
{
    args_config_t args = {0};
    optarg = "-4242";

    cr_assert_eq(p_handler(&args, NULL, 0), FAILURE);
    cr_assert_stderr_eq_str(ERROR_PORT);
}

Test(p_handler, p_handler_null, .init = redirect)
{
    args_config_t args = {0};
    optarg = "0";

    cr_assert_eq(p_handler(&args, NULL, 0), FAILURE);
    cr_assert_stderr_eq_str(ERROR_PORT);
}

// x handler
Test(x_handler, valid_x_handler)
{
    args_config_t args = {0};
    optarg = "4242";

    cr_assert_eq(x_handler(&args, NULL, 0), SUCCESS);
}

Test(x_handler, x_handler_negative, .init = redirect)
{
    args_config_t args = {0};
    optarg = "-4242";

    cr_assert_eq(x_handler(&args, NULL, 0), FAILURE);
    cr_assert_stderr_eq_str(ERROR_WIDTH);
}

Test(x_handler, x_handler_null, .init = redirect)
{
    args_config_t args = {0};
    optarg = "0";

    cr_assert_eq(x_handler(&args, NULL, 0), FAILURE);
    cr_assert_stderr_eq_str(ERROR_WIDTH);
}

// y handler
Test(y_handler, valid_y_handler)
{
    args_config_t args = {0};
    optarg = "4242";

    cr_assert_eq(y_handler(&args, NULL, 0), SUCCESS);
}

Test(y_handler, y_handler_negative, .init = redirect)
{
    args_config_t args = {0};
    optarg = "-4242";

    cr_assert_eq(y_handler(&args, NULL, 0), FAILURE);
    cr_assert_stderr_eq_str(ERROR_HEIGHT);
}

Test(y_handler, y_handler_null, .init = redirect)
{
    args_config_t args = {0};
    optarg = "0";

    cr_assert_eq(y_handler(&args, NULL, 0), FAILURE);
    cr_assert_stderr_eq_str(ERROR_HEIGHT);
}

// f handler
Test(f_handler, valid_f_handler)
{
    args_config_t args = {0};
    optarg = "4242";

    cr_assert_eq(f_handler(&args, NULL, 0), SUCCESS);
}

Test(f_handler, f_handler_negative, .init = redirect)
{
    args_config_t args = {0};
    optarg = "-4242";

    cr_assert_eq(f_handler(&args, NULL, 0), FAILURE);
    cr_assert_stderr_eq_str(ERROR_FREQ);
}

Test(f_handler, f_handler_null, .init = redirect)
{
    args_config_t args = {0};
    optarg = "0";

    cr_assert_eq(f_handler(&args, NULL, 0), FAILURE);
    cr_assert_stderr_eq_str(ERROR_FREQ);
}

// c handler
Test(c_handler, valid_c_handler)
{
    args_config_t args = {0};
    optarg = "4242";

    cr_assert_eq(c_handler(&args, NULL, 0), SUCCESS);
}

Test(c_handler, c_handler_negative, .init = redirect)
{
    args_config_t args = {0};
    optarg = "-4242";

    cr_assert_eq(c_handler(&args, NULL, 0), FAILURE);
    cr_assert_stderr_eq_str(ERROR_CLIENTS);
}

Test(c_handler, c_handler_null, .init = redirect)
{
    args_config_t args = {0};
    optarg = "0";

    cr_assert_eq(c_handler(&args, NULL, 0), FAILURE);
    cr_assert_stderr_eq_str(ERROR_CLIENTS);
}

// h handler
Test(h_handler, help)
{
    args_config_t args = {0};

    cr_assert_eq(h_handler(&args, NULL, 0), SUCCESS);
    cr_assert_eq(args.help, true);
}

// n handler
Test(n_handler, valid_n_handler)
{
    args_config_t args = {0};
    char *const argv[] = {"une", "deux", "trois", "teams", "-p"};

    optind = 1;
    cr_assert_eq(n_handler(&args, argv, 5), SUCCESS);
    free_array(args.team_names);
}

Test(n_handler, valid_n_handler_2)
{
    args_config_t args = {0};
    char *const argv[] = {"une", "deux", "trois", "teams", NULL};

    optind = 1;
    cr_assert_eq(n_handler(&args, argv, 5), SUCCESS);
    free_array(args.team_names);
}

Test(n_handler, valid_n_handler_3)
{
    args_config_t args = {0};
    char *const argv[] = {"une", "deux", "trois", "teams"};

    optind = 1;
    cr_assert_eq(n_handler(&args, argv, 5), SUCCESS);
    free_array(args.team_names);
}
