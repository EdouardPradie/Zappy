/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Camera
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>
#include <array>

constexpr double ZOOM_ADD {0.9};
constexpr double ZOOM_MINUS {1.1};

namespace zappy {

    class Camera {
      public:
        Camera();
        Camera(Camera const& to_copy) = default;
        Camera(Camera&& to_move) = default;
        ~Camera() = default;

        Camera& operator=(Camera const& to_copy) = default;
        Camera& operator=(Camera && to_move) = default;

        void cameraOnKeyPressed(sf::Event &event);
        void cameraOnKeyReleased(sf::Event &event);
        void moveView(sf::RenderWindow &window);

      private:
        sf::View m_view;
        std::array<bool, 7> m_directions;
    };
}
