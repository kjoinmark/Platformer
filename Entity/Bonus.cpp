#include "Bonus.hpp"

Bonus::Bonus(size_t x, size_t y, size_t block_size) :
	boders((x - 1)* block_size, (y - 1)* block_size, 50, 40) {
	used = false;
	points = 500;
}
Bonus::Bonus(Bonus&& bonus) noexcept {
	sprite = std::move(bonus.sprite);
	boders = std::move(bonus.boders);
	used = false;
	points = 500;
}

void Bonus::set_sprite_pos(int frame, int offset_x, int offset_y) {
	if (frame % 2)
		sprite.setTextureRect(sf::IntRect(0, 0, boders.width, boders.height));
	else
		sprite.setTextureRect(sf::IntRect(boders.width, 0, -boders.width, boders.height));

	sprite.setPosition(boders.left - offset_x, boders.top - offset_y);

}
bool Bonus::obj_collision(Base_entity& obj) {
	if (used)
		return false;
	sf::FloatRect obj_rect = obj.get_boders();
	if (!boders.intersects(obj_rect))
		return false;
	return true;
}