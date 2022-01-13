#pragma once
#include "Base_entity.hpp"
#include <SFML/Graphics.hpp>

class Player final : public Base_entity {
	float dx, dy;
	sf::FloatRect boders;
	sf::Sprite sprite;
	size_t hp;
public:
	float immune_timer;
	int move;
	bool on_ground;
	bool immune;
public:
	Player();
	virtual ~Player() = default;
public:
	void set_start(size_t x, size_t  y, size_t block_size);
	void set_texture(sf::Texture& image) {
		sprite.setTexture(image);
	}
	void set_x(const float& x, float time);
	void set_y(const float& y, float time);
	float x_speed() const {
		return dx;
	};
	float y_speed() const {
		return dy;
	};
	void set_dy_zero() {
		dy = 0;
	}
	sf::FloatRect& get_boders() {
		return boders;
	}
public:
	bool map_collision(size_t block_size, int dir, size_t i, size_t j);
	bool mob_collision(Base_entity& obj);
	size_t get_hp() const {
		return hp;
	}
public:
	void set_sprite_pos(int frame, int offset_x, int offset_y) override;
	const sf::Sprite& get_sprite() override;

};



