/*
** EPITECH PROJECT, 2023
** tests
** File description:
** launch
*/

#include <criterion/criterion.h>
#include <criterion/internal/redirect.h>
#include <zappy/config/arguments.h>
#include <zappy/config/config.h>
#include <zappy/server.h>

void redirect(void);

Test(launch, test_null_args)
{
    cr_assert_eq(launch(NULL), FAILURE);
}

Test(launch, test_basic, .init = redirect)
{
    args_config_t args = {0};
    server_t server = {0};

    args.port = DEFAULT_PORT;
    create_server(&server, &args);
    cr_assert_eq(launch(&args), FAILURE);
    cr_assert_stderr_eq_str("Zappy: Address already in use\n");
}

Test(server_loop, null_args)
{
    cr_assert_eq(server_loop(NULL), FAILURE);
}
