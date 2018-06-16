/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#ifndef MATHUTILS_HPP
#define MATHUTILS_HPP

#include <cmath>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#define PI 3.14159264f

float getNorme(const sf::Vector2f u, const sf::Vector2f v);
float getNorme(const sf::Vector3f u, const sf::Vector3f v);

#endif