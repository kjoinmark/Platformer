#include "World.hpp"
#include "World.hpp"
#include <iostream>

World::World(Texture_Pack& texture_pack, Sound_Pack& sound_pack, const std::string& map, sf::Vector2u size) :_map(map, 32), 
window_width(size.x), window_height(size.y), _ground(&texture_pack.ground), _texture_pack(texture_pack), _sound_pack(sound_pack) {
	offset_x = 0;
	offset_y = 0;
	shoot_pause = 0;
	score = 0;
	win = false;
	_player.set_texture(texture_pack.player);
	_portal.set_texture(texture_pack.portal);
	_background.setTexture(texture_pack.background);
	hp.setTexture(texture_pack.hp_texture);
	std::pair<size_t, size_t> player_pos = _map.one_spawn('P');
	_player.set_start(player_pos.first, player_pos.second, _map.block_size);

	std::pair<size_t, size_t> portal_pos = _map.one_spawn('O');
	_portal.set_start(portal_pos.first, portal_pos.second, _map.block_size);

	std::vector<std::pair<size_t, size_t>> spawns = _map.spawns('M');
	for (auto&& it : spawns) {
		mobs.emplace_back(it.first, it.second, _map.block_size);
		mobs.back().set_texture(texture_pack.mobs);
	}
	spawns.clear();
	spawns = _map.spawns('D');
	for (auto&& it : spawns) {
		bonus.emplace_back(it.first, it.second, _map.block_size);
		bonus.back().set_texture(texture_pack.bonus);
	}
	font = texture_pack.font;
	text_score.setFont(font);
	text_score.setString("Score: " + std::to_string(score));
	text_score.setCharacterSize(30);
};

bool World::update(float time, float& current_frame) {
	_player.set_x(0, 0);
	int mode = 0;
	
	mobs_handler(time, current_frame);

	size_t hp_i = _player.get_hp();
	if (hp_i == 0)
		return false;

	keyboard_handler(time, current_frame);
	fireball_handler(time, current_frame);
	bonus_handler(time, current_frame);
	
	if (!_player.on_ground) {
		_player.set_y(0.0005 * time, time);
	}
	if (!map_collision(1))
		_player.on_ground = false;
	current_frame += 0.004 * time;

	if (_portal.obj_collision(_player)) {
		win = true;
		return false;
	}

	_portal.set_sprite_pos(current_frame, offset_x, offset_y);
	_player.set_sprite_pos(current_frame, offset_x, offset_y);

	if (_player.get_boders().left > 400) offset_x = _player.get_boders().left - 400;
	offset_y = _player.get_boders().top - 200;
	
	text_score.setString("Score " + std::to_string(score));
	
	return true;
	
}

void World::render(sf::RenderWindow& window) {
	window.draw(_background);

	sf::RectangleShape rectangle(sf::Vector2f(_map.block_size, _map.block_size));
	for (int i = 0; i < _map.get_height(); i++)
		for (int j = 0; j < _map.get_width(); j++) {
			if (_map.is_block(j, i)) rectangle.setTexture(_ground);
			else
				continue;
			rectangle.setPosition(j * _map.block_size - offset_x, i * _map.block_size - offset_y);
			window.draw(rectangle);
		}
	for (auto&& it : mobs) {
		if (it.visible && it.is_alive())
			window.draw(it.get_sprite());
	}
	for (auto&& it : fireballs) {
		if (it.is_alive())
			window.draw(it.get_sprite());
	}
	for (auto&& it : bonus) {
		if (!it.is_used())
			window.draw(it.get_sprite());
	}

	window.draw(_portal.get_sprite());
	window.draw(_player.get_sprite());
	size_t hp_i = _player.get_hp();
	hp.setTextureRect(sf::IntRect(0, 0, 34 * hp_i, 26));
	text_score.setPosition(0, 30);
	window.draw(hp);
	window.draw(text_score);
	

}

void World::restart() {
	offset_x = 0;
	offset_y = 0;
	shoot_pause = 0;
	score = 0;
	win = false;
	std::pair<size_t, size_t> player_pos = _map.one_spawn('P');
	_player.set_start(player_pos.first, player_pos.second, _map.block_size);

	std::pair<size_t, size_t> portal_pos = _map.one_spawn('O');
	_portal.set_start(portal_pos.first, portal_pos.second, _map.block_size);

	mobs.clear();
	std::vector<std::pair<size_t, size_t>> spawns = _map.spawns('M');
	for (auto&& it : spawns) {
		mobs.emplace_back(it.first, it.second, _map.block_size);
		mobs.back().set_texture(_texture_pack.mobs);
	}
	spawns.clear();
	bonus.clear();
	spawns = _map.spawns('D');
	for (auto&& it : spawns) {
		bonus.emplace_back(it.first, it.second, _map.block_size);
		bonus.back().set_texture(_texture_pack.bonus);

	}
	
	text_score.setString("Score: " + std::to_string(score));
}

bool World::map_collision(int dir) {
	bool is_coll = false;
	sf::FloatRect& p_rect = _player.get_boders();
	for (size_t i = p_rect.top / _map.block_size; i < (p_rect.top + p_rect.height) / _map.block_size; i++) {
		for (size_t j = p_rect.left / _map.block_size; j < (p_rect.left + p_rect.width) / _map.block_size; j++) {
			if (_map.is_block(j, i)) {
				//	is_coll = _player.map_collision(_map.block_size, dir, i, j);
				if ((_player.x_speed() > 0) && (dir == 0)) {
					p_rect.left = j * _map.block_size - p_rect.width;
				}
				if ((_player.x_speed() < 0) && (dir == 0)) {
					p_rect.left = j * _map.block_size + _map.block_size;
				}
				if ((_player.y_speed() > 0) && (dir == 1)) {
					p_rect.top = i * _map.block_size - p_rect.height;
					_player.set_dy_zero(); _player.on_ground = true;
					is_coll = true;
				}
				if ((_player.y_speed() < 0) && (dir == 1)) {
					p_rect.top = i * _map.block_size + _map.block_size;
					is_coll = true;
				}
			}
		}
	}
	return is_coll;
}

bool World::mobs_collision(bool immune) {
	if (mobs.empty())
		return false;
	bool attack = false;
	for (auto&& it : mobs) {
		for (auto&& it_f : fireballs) {
			if (it.is_alive()) {
				if (it_f.obj_collision(it)) {
					score += 100;
					it_f.kill();
					it.kill();
				}
			}
		}
		sf::FloatRect& m_rect = it.get_boders();
		for (size_t i = m_rect.top / _map.block_size; i < (m_rect.top + m_rect.height) / _map.block_size; i++) {
			for (size_t j = m_rect.left / _map.block_size; j < (m_rect.left + m_rect.width) / _map.block_size; j++) {
				if (_map.is_block(j, i)) {
					if (it.x_speed() > 0) {
						m_rect.left = j * _map.block_size - m_rect.width; it.change_dir();
					}
					else if (it.x_speed() < 0) {
						m_rect.left = j * _map.block_size + _map.block_size;  it.change_dir();
					}
				}


			}
		}
		if (!immune && it.is_alive()) {
			if (_player.mob_collision(it))
				attack = true;
		}
	}
	return attack;
}

void World::fireball_handler(float time, float current_frame) {
	for (auto&& it : fireballs) {
		if (_map.is_block(it.get_x() / _map.block_size, it.get_y() / _map.block_size)) {
			it.kill();
		}
		it.set_x(time);
		if (it.get_x() > window_width + offset_x)
			it.kill();
		it.set_sprite_pos(current_frame, offset_x, offset_y);
	}
	for (int i = 0; i < fireballs.size(); i++) {
		if (!fireballs.at(i).is_alive())
			fireballs.pop_front();
		else
			break;
	}
}

void World::keyboard_handler(float time, float current_frame) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		_player.set_x(-0.15, time);
		map_collision(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		_player.set_x(0.15, time);
		map_collision(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (_player.on_ground) {
			_player.set_y(-0.38, time); _player.on_ground = false;
			_sound_pack.jump.play();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && current_frame > shoot_pause) {
		shoot_pause = current_frame + 5;
		fireballs.emplace_back(_player.get_boders().left + _player.get_boders().width / 2,
			_player.get_boders().top + 30, _player.move);
		fireballs.back().set_texture(_texture_pack.fireball);
		_sound_pack.fire.play();

	}

}

void World::mobs_handler(float time, float current_frame) {
	for (auto&& it : mobs) {
		if (it.get_boders().left > window_width + offset_x)
			it.visible = false;
		else {
			it.visible = true;
			it.set_x(1, time);
			it.set_sprite_pos(current_frame, offset_x, offset_y);
		}
	}
	if (mobs_collision(_player.immune)) {
		score -= 150;
		_player.immune_timer = current_frame + 15;
		_player.immune = true;
	}


	if (current_frame > _player.immune_timer) {
		_player.immune = false;
	}
}

void World::bonus_handler(float time, float current_frame) {
	for (auto&& it : bonus) {
		if (it.obj_collision(_player)) {
			if (!it.is_used())
				score += it.get_points();
			it.set_used();
		}
		it.set_sprite_pos(current_frame, offset_x, offset_y);
	}
}