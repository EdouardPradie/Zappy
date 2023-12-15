/*
** EPITECH PROJECT, 2023
** gui
** File description:
** AScene
*/

#pragma once

#include <zappy/Scenes/IScene.hh>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace zappy
{

    class AScene : public IScene
    {
        public:
            AScene() = default;
            AScene(AScene const &to_copy) = default;
            AScene(AScene &&to_move) = default;
            ~AScene() override = default;

            AScene &operator=(AScene const &to_copy) = default;
            AScene &operator=(AScene &&to_move) = default;

        protected:
            sf::Sprite m_sprite;
            sf::Texture m_texture;
    };
} // namespace zappy
