#pragma once
#include "Base_entity.hpp"

class Mob final :public Base_entity {
	float dx, dy;
	sf::FloatRect boders;
	sf::Sprite sprite;
	bool alive;
public:
	bool visible;
public:	
	Mob() {
		dx = 0.1;
		dy = 0;
		alive = true;
		visible = true;
	}
	Mob(float x, float y, size_t block_size); 
	Mob(Mob&& mob) noexcept;
public:
	void kill() {
		alive = false;
	}
	bool is_alive() const {
		return alive;
	}
	void set_alive() {
		alive = true;
	}
public:
	void set_texture(sf::Texture& image) {
		sprite.setTexture(image);
	}
	void set_start(size_t x, size_t  y, size_t block_size);
	void set_x(const float& x, float time) {
		boders.left += dx * time;
	};
	float x_speed() const {
		return dx;
	};
	void change_dir() {
		dx *= -1;
	};
	sf::FloatRect& get_boders() override {
		return boders;
	}
public:
	void set_sprite_pos(int frame, int offset_x, int offset_y) override;
	const sf::Sprite& get_sprite() override {
		return sprite;
	}

	bool map_collision(size_t block_size, size_t i, size_t j);
};

