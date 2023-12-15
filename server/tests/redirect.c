/*
** EPITECH PROJECT, 2023
** tests
** File description:
** redirect
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect(void)
{
    cr_redirect_stderr();
    cr_redirect_stdout();
}
