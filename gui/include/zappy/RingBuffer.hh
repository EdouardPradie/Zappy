/*
** EPITECH PROJECT, 2023
** gui
** File description:
** RingBuffer
*/

#pragma once

#include <array>
#include <cstddef>

namespace zappy
{

    class RingBuffer
    {
        public:
            RingBuffer();
            RingBuffer(RingBuffer const &to_copy) = delete;
            RingBuffer(RingBuffer &&to_move) = default;
            ~RingBuffer() = default;

            RingBuffer &operator=(RingBuffer const &to_copy) = delete;
            RingBuffer &operator=(RingBuffer &&to_move) = default;

            void push(char value);
            char front();
            void clear();
            [[nodiscard]] bool isWritable() const;

        private:
            static const std::size_t m_capacity = 4092;
            std::size_t m_begin = 1364;
            std::size_t m_end = 1364;
            std::array<char, m_capacity> m_array{};
            bool m_is_write_okay = true;
    };
} // namespace zappy
