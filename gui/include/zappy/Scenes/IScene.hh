/*
** EPITECH PROJECT, 2023
** gui
** File description:
** IScene
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

namespace zappy
{

    class IScene
    {
        public:
            IScene() = default;
            IScene(IScene const &to_copy) = default;
            IScene(IScene &&to_move) = default;
            virtual ~IScene() = default;

            IScene &operator=(IScene const &to_copy) = default;
            IScene &operator=(IScene &&to_move) = default;

            virtual void draw(sf::RenderWindow &window) = 0;
            virtual void manageEvent(sf::RenderWindow &window, sf::Event &event,
                                     std::vector<std::string> &command_to_send) = 0;
    };
} // namespace zappy
