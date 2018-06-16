#include "Utils/MathUtils.hpp"

float getNorme(const sf::Vector2f u, const sf::Vector2f v) { return sqrtf((v.x - u.x)*(v.x - u.x) + (v.y - u.y)*(v.y - u.y)); }
float getNorme(const sf::Vector3f u, const sf::Vector3f v) { return sqrtf((v.x - u.x)*(v.x - u.x) + (v.y - u.y)*(v.y - u.y) + (v.z - u.z)*(v.z - u.z)); }