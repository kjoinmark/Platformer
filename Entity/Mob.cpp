#include "Mob.hpp"


Mob::Mob(float x, float y, size_t block_size) {
	boders = sf::FloatRect((x - 1) * block_size, (y - 1) * block_size, 62, 42);
	dx = 0.1;
	dy = 0;
	alive = true;
	visible = true;
}

Mob::Mob(Mob&& mob) noexcept {
	sprite = std::move(mob.sprite);
	boders = std::move(mob.boders);
	dx = 0.1;
	dy = 0;
	alive = true;
	visible = true;
};


void Mob::set_start(size_t x, size_t  y, size_t block_size) {
	boders.left = x * block_size;
	boders.top = y * block_size;
}

bool Mob::map_collision(size_t block_size, size_t i, size_t j) {
	if (dx > 0) {
		boders.left = j * block_size - boders.width; dx *= -1;
	}
	else if (dx < 0) {
		boders.left = j * block_size + block_size;  dx *= -1;
	}
	return true;
}


void Mob::set_sprite_pos(int frame, int offset_x, int offset_y) {
	frame = frame % 2;
	if (dx > 0) sprite.setTextureRect(sf::IntRect(boders.width * int(frame) + 123, 4, boders.width, boders.height));
	if (dx < 0) sprite.setTextureRect(sf::IntRect(boders.width * int(frame) + 123 + boders.width, 4, -boders.width, boders.height));
	sprite.setPosition(boders.left - offset_x, boders.top - offset_y);

}