/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ZappyError
*/

#pragma once

#include <exception>
#include <string>

namespace zappy
{
    class ZappyException : public std::exception
    {
        public:
            ZappyException(std::string perror_msg) : error_msg{std::move(perror_msg)}
            {
            }

            ZappyException(ZappyException const &to_copy) = delete;
            ZappyException(ZappyException &&to_move) = delete;
            ~ZappyException() override = default;
            ZappyException &operator=(ZappyException const &to_copy) = default;

            [[nodiscard]] const char *what() const noexcept override;

        private:
            std::string error_msg;
    };

} // namespace zappy
