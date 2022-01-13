
#include "Player.hpp"
#include "Base_entity.hpp"
#include <SFML/Graphics.hpp>



Player::Player() {
	boders = sf::FloatRect(7 * 32, 9 * 32, 76, 93);
	dx = dy = 0.15;
	on_ground = false;
	immune = false;
	move = 1;
	hp = 3;
}

void Player::set_start(size_t x, size_t  y, size_t block_size) {
		boders.left = x * block_size;
		boders.top = y * block_size;
		dx = dy = 0.15;
		on_ground = false;
		immune = false;
		move = 1;
		hp = 3;
		immune_timer = 0;
	}

bool Player::map_collision(size_t block_size, int dir, size_t i, size_t j) {
	bool is_coll = false;
	if ((dx > 0) && (dir == 0)) {
		boders.left = j * block_size - boders.width;
	}
	if ((dx < 0) && (dir == 0)) {
		boders.left = j * block_size + block_size;
	}
	if ((dy > 0) && (dir == 1)) {
		boders.top = i * block_size - boders.height;
		set_dy_zero(); on_ground = true;
		is_coll = true;
	}
	if ((dy < 0) && (dir == 1)) {
		boders.top = i * block_size + block_size;
		is_coll = true;
	}
	return is_coll;
}


void Player::set_x(const float& x, float time) {
	if (x > 0)
		move = 1;
	if (x < 0)
		move = -1;

	dx = x;
	boders.left += x * time;
};

void Player::set_y(const float& y, float time) {
	dy += y;
	boders.top += dy * time;
};

void Player::set_sprite_pos(int frame, int offset_x, int offset_y) {
	frame = frame % 3;
	if (dx > 0) sprite.setTextureRect(sf::IntRect(boders.width * int(frame + 1), 0, boders.width, boders.height));
	if (dx < 0) sprite.setTextureRect(sf::IntRect(boders.width * int(frame + 1) + boders.width, 0, -boders.width, boders.height));
	if (on_ground == true && dx == 0) {
		if (move == 1)
			sprite.setTextureRect(sf::IntRect(0, 0, boders.width, boders.height));
		else
			sprite.setTextureRect(sf::IntRect(boders.width, 0, -boders.width, boders.height));
	}
	sprite.setPosition(boders.left - offset_x, boders.top - offset_y);
};

const sf::Sprite& Player::get_sprite() {
	if (!immune) {
		sprite.setColor(sf::Color::White);
		return sprite;
	}
	sf::Color grey(200, 120, 120);
	sprite.setColor(grey);
	return sprite;
}

bool Player::mob_collision(Base_entity& obj) {
	sf::FloatRect obj_boders = obj.get_boders();
	bool coll = boders.intersects(obj_boders);
	if (coll) {
		hp--;
		return true;
	}
	return false;
}