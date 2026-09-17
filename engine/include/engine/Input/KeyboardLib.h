#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <array>
#include <map>
#include <vector>
constexpr inline int KEY_BUFFER_DURATION = 5;

constexpr sf::Keyboard::Key W = sf::Keyboard::Key::W;
constexpr sf::Keyboard::Key S = sf::Keyboard::Key::S;
constexpr sf::Keyboard::Key A = sf::Keyboard::Key::A;
constexpr sf::Keyboard::Key D = sf::Keyboard::Key::D;
constexpr std::array<sf::Keyboard::Key, 4> MOVEMENT_KEYS = { W, S, A, D };

const std::map<sf::Keyboard::Key, std::vector<sf::Keyboard::Key>> VALID_DIAGONAL_MOVE_COMP = {
    { W, { A, D } }, { S, { A, D } }, { A, { W, S } }, { D, { W, S } } };
