#pragma once
#include "Base_entity.hpp"

class Bonus final: Base_entity {
	sf::Sprite sprite;
	sf::FloatRect boders;
	size_t points;
	bool used;
public:
	Bonus(size_t x, size_t y, size_t block_size);
	Bonus(Bonus&& bonus) noexcept;
public:
	bool is_used() const {
		return used;
	}
	void set_used(){
		used = true;
	}	
	void set_unused() {
		used = false;
	}
	size_t get_points() const {
		return points;
	}
	void set_texture(sf::Texture& image) {
		sprite.setTexture(image);
	}
	sf::FloatRect& get_boders() override {
		return boders;
	}
public:
	const sf::Sprite& get_sprite() override {
		return sprite;
	}
	void set_sprite_pos(int frame, int offset_x, int offset_y) override;
	bool obj_collision(Base_entity& obj);
};

