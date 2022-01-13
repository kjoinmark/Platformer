#include "Fireball.hpp"

Fireball::Fireball(size_t x, size_t y, float dir) : pos_x(x), pos_y(y) {
	dx = dir * 0.2;
	pic = 40;
	alive = true;
}

Fireball::Fireball(Fireball&& fire) noexcept {
	sprite = std::move(fire.sprite);
	pos_x = fire.pos_x;
	pos_y = fire.pos_y;
	pic = fire.pic;
	dx = 0.2;
	alive = true;
}

bool Fireball::obj_collision(Base_entity& obj) {
	if (!alive)
		return false;
	sf::FloatRect boders = obj.get_boders();
	if (boders.top > pos_y || boders.top + boders.height < pos_y)
		return false;
	if (boders.left > pos_x || boders.left + boders.width < pos_x)
		return false;
	alive = false;
	return true;
}

void Fireball::set_sprite_pos(int frame, int offset_x, int offset_y) {
	frame = frame % 4;
	if (alive) sprite.setTextureRect(sf::IntRect(frame * pic, 0, pic, pic));
	if (!alive) sprite.setTextureRect(sf::IntRect(frame * pic, pic, pic, pic));
	sprite.setPosition(pos_x - offset_x, pos_y - offset_y);

}