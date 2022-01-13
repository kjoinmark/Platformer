#pragma once
#include "Base_entity.hpp"


class Portal final:Base_entity {
	sf::Sprite sprite;
	sf::FloatRect boders;
	bool used;
public:
	Portal() {
		used = false;
	}
	Portal(size_t x, size_t y, size_t block_size) :
		boders(x* block_size - 60 + block_size, y* block_size - 140 + block_size, 60, 140) {
		used = false;
	}
public:
	void set_texture(sf::Texture& image) {
		sprite.setTexture(image);
	}
	void set_start(size_t x, size_t y, size_t block_size) {
		boders.left = x * block_size - 60 + block_size;
		boders.top = y * block_size - 140 + block_size;
		boders.width = 60;
		boders.height = 140;
		used = false;
	}
	bool is_used() {
		return used;
	}
public:
	sf::FloatRect& get_boders() override {
		return boders;
	}
	const sf::Sprite& get_sprite() override {
		return sprite;
	}
	void set_sprite_pos(int frame, int offset_x, int offset_y) override {
		size_t pic = frame % 4;
		sprite.setTextureRect(sf::IntRect(60 * pic, 0, boders.width, boders.height));
		sprite.setPosition(boders.left - offset_x, boders.top - offset_y);
	}
public:
	bool obj_collision(Base_entity& obj) {
		const sf::FloatRect obj_rect = obj.get_boders();
		if (!boders.intersects(obj_rect))
			return false;
		return true;
	}
};

