#pragma once
#include "Map.hpp"
#include "Packs.hpp"
#include "./Entity/Player.hpp"
#include "./Entity/Fireball.hpp"
#include "./Entity/Mob.hpp"
#include "./Entity/Bonus.hpp"
#include "./Entity/Portal.hpp"
#include <string>
#include <vector>
#include <deque>

class World {
	Map _map;
	Player _player;
	Portal _portal;
	std::vector<Mob> mobs;
	std::vector<Bonus> bonus;
	std::deque<Fireball> fireballs;
private:
	sf::Text text_score;
	sf::Font font;
	Texture_Pack& _texture_pack;
	Sound_Pack& _sound_pack;
	const sf::Texture* _ground;
	sf::Sprite _background;
	sf::Sprite hp;
private:
	const size_t window_width;
	const size_t window_height;
	int offset_x;
	int offset_y;
	bool win;
	int score;
	float shoot_pause;
private:
	bool map_collision(int dir);
	bool mobs_collision(bool immune);
private:
	void keyboard_handler(float time, float current_frame);
	void mobs_handler(float time, float current_frame);
	void fireball_handler(float time, float current_frame);
	void bonus_handler(float time, float current_frame);
public:
	World(Texture_Pack& texture_pack, Sound_Pack& sound_pack,
		const std::string& map, sf::Vector2u size);
public:
	bool update(float time, float& current_frame);
	void render(sf::RenderWindow& window);
	const sf::Text& get_score() const {
		return text_score;
	}

	bool is_win() const {
		return win;
	}
	void restart();
};