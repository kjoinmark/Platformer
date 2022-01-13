#pragma once

#include <SFML/Graphics.hpp>


class Base_entity {
public:
	virtual ~Base_entity() = default;
	//set sptire position with screen offset
	virtual void set_sprite_pos(int frame, int offset_x, int offset_y) = 0;
	//return sprite of the object
	virtual const sf::Sprite& get_sprite() = 0;
	//return boaders of object's sprite
	virtual sf::FloatRect& get_boders() = 0;
};

