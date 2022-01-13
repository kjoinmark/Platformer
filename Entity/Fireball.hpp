#pragma once

#include <SFML/Graphics.hpp>
#include "Base_entity.hpp"

class Fireball final :Base_entity {
	sf::Sprite sprite;
	sf::FloatRect boders;
	size_t pic;
	float pos_x, pos_y;
	float dx;
	bool alive;
public:
	Fireball() {
		dx = 0;
		pos_x = 0;
		pos_y = 0;
		pic = 40;
		alive = true;
	}
	Fireball(size_t x, size_t y, float dir);
	Fireball(Fireball&& fire) noexcept;
public:
	void kill() {
		alive = false;
	}
	bool is_alive() {
		return alive;
	}
public:
	void set_texture(sf::Texture& image) {
		sprite.setTexture(image);
	}
	void set_x(float time) {
		pos_x += dx * time;
	}
	float get_x() const {
		return pos_x;
	}
	float get_y() const {
		return pos_y;
	}
public:
	const sf::Sprite& get_sprite() override {
		return sprite;
	}
	void set_sprite_pos(int frame, int offset_x, int offset_y) override;
	bool obj_collision(Base_entity& obj);
	sf::FloatRect& get_boders() override {
		return boders;
	}

};

